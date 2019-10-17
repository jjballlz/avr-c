/***************************************
 *
 * File >>_> main.c
 * 
 * Creation date >>_> 05.10-2019
 * Last modified >>_> Sun 06 Oct 2019 08:11:08 PM CEST
 *
 * Author >>_> gian.SANDRI
 *
 ***************************************/

// define
#define F_CPU 16000000L
// include
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
//#include "avr_helper_functions.h"

/*
 *OUTPUTS
 */
const int dP1 = DDD4;
const int dP2 = DDD3;
const int dP3 = DDD2;

const int dbuzz1 = DDD5;
const int dbuzz2 = DDD6;

/*
 * INPUTS
 */
const int bS1 = DDB3;
const int bS2 = DDB4;
const int bS3 = DDB5;

// LEDstates
bool ledStatedP1 = 0;
bool ledStatedP2 = 0;
bool ledStatedP3 = 0;

// buttonWatch
// bool buttonWatch_bS1=1;
// bool buttonWatch_bS2=1;
// bool buttonWatch_bS3=1;

// timer
unsigned long timeCounter = 0;

int cycleFreq = 100;

int main(void) {
	/*
	 *SETUP
	 */
	// initialize dataRegistries
	initializeValues();

	setIO_T();

	/*
	 *	<MAIN_LOOP>
	 */
	while (1) {
		setStates();
		writeLEDvalues();
	}
}

void initializeValues() {
	DDRD = 0xFF;
	PORTD = 0x00;

	DDRB = 0xFF;
	PORTB = 0x00;

	DDRC = 0xFF;
	PORTC = 0x00;
}

void setIO_T() {
	// set timer TCCR0A as CTC
	TCCR0A |= (1 << WGM01);
	// set the compare register (value that you want to count to - here 14)
	OCR0A = 0x10;
	// set to compare match A, interrupt enabled (sets the ISR COMPA vector)
	TIMSK0 |= (1 << OCIE0A);
	sei();  // enable interrups
	// set prescaler and start the timer
	TCCR0B |= (1 << CS00);

	// outputs-LEDs (1)
	DDRD |= (1 << dP1);

	DDRD |= (1 << dP2);

	DDRD |= (1 << dP3);

	// inputs-pullups -> (0) in ddrb and (1) in portx
	DDRB &= ~(1 << bS1);
	PORTB |= (1 << bS1);

	DDRB &= ~(1 << bS2);
	PORTB |= (1 << bS2);

	DDRB &= ~(1 << bS3);
	PORTB |= (1 << bS3);

	// Buzzer
	DDRD |= (1 << dbuzz1);
	DDRD |= (1 << dbuzz2);
	PORTD |= (1 << dbuzz1);
}

void setStates() {
	if (!(PINB & (1 << bS1))) {
		ledStatedP1 = 1;
		ledStatedP2 = 1;
		ledStatedP3 = 1;
		//+buzzer
		buzzz();
	} else {
		// P1
		if ((PINB & (1 << bS2)) && (PINB & (1 << bS3))) {
			ledStatedP1 = 1;
		} else {
			ledStatedP1 = 0;
		}

		// P2
		if (PINB & (1 << bS2)) {
			ledStatedP2 = 1;
		} else {
			ledStatedP2 = 0;
		}

		// P3
		if ((PINB & (1 << bS2)) || (PINB & (1 << bS3))) {
			ledStatedP3 = 1;
		} else {
			ledStatedP3 = 0;
		}
	}
}

void writeLEDvalues() {
	// P1
	if (ledStatedP1) {
		PORTD &= ~(1 << dP1);
	} else {
		PORTD |= (1 << dP1);
	}

	// P2
	if (ledStatedP2) {
		PORTD &= ~(1 << dP2);
	} else {
		PORTD |= (1 << dP2);
	}

	// P3
	if (ledStatedP3) {
		PORTD &= ~(1 << dP3);
	} else {
		PORTD |= (1 << dP3);
	}
}

void buzzz() {
	if (timeCounter > cycleFreq) {
		if (PORTD & (1 << dbuzz1)) {
			PORTD &= ~(1 << dbuzz1);
		} else if (!(PORTD & (1 << dbuzz1))) {
			PORTD |= (1 << dbuzz1);
		}
		timeCounter = 0;
	}
}

ISR(TIMER0_COMPA_vect) {
	// Interrupt, here we time
	++timeCounter;
	if (timeCounter > 64000) {
		timeCounter = 0;
	}
}

