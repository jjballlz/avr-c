/***************************************
 *
 * File >>_> main.c
 *
 * Creation date >>_> 12.10-2019
 * Last modified >>_> Thu 17 Oct 2019 01:29:50 PM CEST
 *
 * Author >>_> gian.SANDRI
 *
 ***************************************/

// define
#define F_CPU 16000000UL
// include
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

#include "main.h"
#include "helpers/SPI_LIB.h"
#include "helpers/max_libs.h"

// addresses and instrucitons
uint8_t _addr1 = 0x00;
uint8_t _instruction1 = 0x00;

uint8_t _addr0 = 0x00;
uint8_t _instruction0 = 0x00;

int main(void) {
	/************************
	 *	<SETUP>
	 ************************/
	// initialize data registries
	initializeValues();

	// Configure OUTPUTS/INPUTS || TIMER-S || COMMUNICATION (spi/uart/i2c)
	setIO_T();

	// initialize matrixs
	initDisplay();

	// init game state
	gameInit(&gameState, &snake);

	/************************
	 *	<MAIN_LOOP>
	 ************************/
	while (1) {
		// test
		matrixWrite(&gameState, &snake);
		_delay_ms(1000);
	}
}

void initializeValues() {
	DDRD = 0x00;
	DDRB = 0x00;
	DDRC = 0x00;
}

void setIO_T() {
	/*start SPI -- see SPI_LIB.h */
	SPI_init();
}

void gameInit(GameState* gameState, Snake* snake[128]) {
	/************************
	 *     GAME_INIT
	 ************************/
	gameState->numberOfDots = 3;
	gameState->directon = 0;
	snake[127]->x = 9;
	snake[127]->y = 4;
	snake[126]->x = 8;
	snake[126]->y = 4;
	snake[125]->x = 7;
	snake[125]->y = 4;
}
