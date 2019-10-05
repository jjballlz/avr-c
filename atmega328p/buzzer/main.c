/***************************************
 *
 * File >>_> main.c
 * 
 * Creation date >>_> 05.10-2019
 * Last modified >>_> Sat 05 Oct 2019 04:44:57 PM CEST
 *
 * Author >>_> gian.SANDRI
 *
 ***************************************/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>

// define
#define F_CPU 16000000L

/*
 * OUTPUTS
 */
const int dBuzzer1 = DDD5;
const int dBuzzer2 = DDD6;

/*
 * INPUTS
 */
const int bS1 = DDD3;
const int bS1 = DDD4;

bool buzzFlag = 0;

// CLOCKS
unsigned long timeCounter = 0;
int dutyCycle;

int main(void){
	
}

