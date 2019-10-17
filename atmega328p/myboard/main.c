/***************************************
 *
 * File >>_> main.c
 *
 * Creation date >>_> 07.10-2019
 * Last modified >>_> Mon 07 Oct 2019 10:09:46 PM CEST
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

/*
 *OUTPUTS
 */
// LED
const int bP1 = DDB3;
// buzzer
const int buzzer = DDB1;
const int buzzerOUT = DDB2;

/*
 * INPUTS
 */
const int dS1 = DDD4;

/*
 * VARIBALES
 */

bool buttonState = 1;

bool ledState = 0;

int main(void) {
	/*
	 *	<SETUP>
	 */

	// initialize dataRegistries
	initializeValues();

	// Configure pins and TIMER0/1A/B
	setIO_T();

	/*
	 *	<MAIN_LOOP>
	 */
	while (1) {
		if (!(PINB & ( 1 << dS1 ))) {
			buttonState = 0;
		}else{
			if (buttonState == 0) {
				ledState = !ledState;
			}
		}
		if (ledState) {
			PORTB |= ( 1 << bP1 );
		}else{
			PORTB &= ~( 1 << bP1 );
		}
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
	// outputs

	// LED
	DDRB |= (1 << bP1);

	// Buzzer-out
	DDRB |= (1 << buzzer);
	// buzer-in
	DDRB &= ~(1 << buzzerOUT);

	// intputs-button
	DDRD |= (1 << dS1);
	PORTB &= ~( 1 << dS1 );
}
