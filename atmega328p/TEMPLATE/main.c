// define
#define F_CPU 
// include
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>

/*
 *OUTPUTS
 */


/*
 * INPUTS
 */



int main(void) {
	/*
	 *	<SETUP>
	 */

	// initialize dataRegistries
	initializeValues();

	//Configure pins and TIMER0/1A/B
	setIO_T();

	/*
	 *	<MAIN_LOOP>
	 */
	while (1) {
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
	
}
