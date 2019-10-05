/***************************************
 *
 * File >>_> main.c
 *
 * Creation date >>_> 05.10-2019
 * Last modified >>_> Sat 05 Oct 2019 04:41:58 PM CEST
 *
 * Author >>_> gian.SANDRI
 *
 ***************************************/

//define
#define F_CPU 16000000L
//include
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
//#include "avr_helper_functions.h"

//LED
const int dP2 = DDD3;

//buttons
const int bS1 = DDB3;
const int bS2 = DDB4;
const int bS3 = DDB5;

bool ledStatedP2=0;
bool buttonWatch=1;

int main(void)
{
	initializeValues();
	setIO_T();
    while (1) 
    {
		if(!(PINB & (1 << bS1))){
			buttonWatch=0;
			_delay_ms(20);
		}else{
			if (!buttonWatch){
				buttonWatch=1;
				ledStatedP2 = !ledStatedP2;
			}
		}
		
		if(!(PINB & (1 << bS2)) && ledStatedP2){
			++OCR2B;
			_delay_ms(1);
			if(OCR2B >= 254){OCR2B = 254;}
		}
		if(!(PINB & (1 << bS3)) && ledStatedP2){
			--OCR2B;
			_delay_ms(1);
			if(OCR2B <= 1){OCR2B=1;}
		}
		
		if(!ledStatedP2){
			OCR2B = 0;
		}else{
			if(OCR2B == 0){
				OCR2B = 127;
			}
		}
    }
}

void initializeValues (){
	DDRD = 0xFF;
	PORTD = 0x00;
	
	DDRB = 0xFF;
	PORTB = 0x00;
	
	DDRC = 0xFF;
	PORTC = 0x00;
}

void setIO_T(){
	//set timer FAST_PWM, inverting mode, no prescale
	TCCR2B |= (1 << WGM21) | (1 << WGM20) | (1 << COM2B0) | (1 << COM2B1) | (1 << CS20);
	TCCR2A |= (1 << COM2B1) | (1 << WGM20);
	//clear PWM marker
	OCR2B = 0;
	
	//outputs-LEDs (1)
	DDRD |= (1 << dP2);
	
	//inputs-pullups -> (0) in ddrb and (1) in portx
	DDRB &= ~(1 << bS1);
	PORTB |= (1 << bS1);
	
	DDRB &= ~(1 << bS2);
	PORTB |= (1 << bS2);

	DDRB &= ~(1 << bS3);
	PORTB |= (1 << bS3);
}
