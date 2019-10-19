/***************************************
 *
 * File >>_> main.c
 *
 * Creation date >>_> 12.10-2019
 * Last modified >>_> Sat 19 Oct 2019 06:04:18 PM CEST
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
#include <stdlib.h>
#include <util/delay.h>

#include "main.h"
#include "helpers/SPI_LIB.h"
#include "helpers/max_libs.h"
#include "helpers/splashes.h"

uint16_t dead = 0;

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
	gameInit(&gameState, snake, &food);

	/************************
	 *	<MAIN_LOOP>
	 ************************/
	while (1) {
		// test
		matrixWrite(&gameState, snake, &food);
		_delay_ms(100);
		keypress(&gameState);
		scroll(&gameState, snake);
		event(&gameState, snake, &food);
		correct_me_if_im_wrong(&gameState, snake, &food);
	}
}

void initializeValues() {
	DDRD = 0x00;
	DDRB = 0x00;
	DDRC = 0x00;
}

void setIO_T() {
	/*start SPI -- see SPI_LIB.c */
	SPI_init();

	// buttons as inputs (0) and pullups (1)
	DDRD &= ~(1 << _UP) & ~(1 << _DOWN) & ~(1 << _LEFT) & ~(1 << _RIGHT);
	PORTD |= (1 << _UP) | (1 << _DOWN) | (1 << _LEFT) | (1 << _RIGHT);
}

void gameInit(GameState* gameState, Snake snake[128], Food* food) {
	/************************
	 *     GAME_INIT
	 ************************/
	gameState->numberOfDots = 3;
	gameState->directon = 0;
	snake[127].x = 9;
	snake[127].y = 4;
	snake[126].x = 8;
	snake[126].y = 4;
	snake[125].x = 7;
	snake[125].y = 4;

	food->x = rand() % 16 + 1;
	food->y = rand() % 8 + 1;
}

void scroll(GameState* gameState, Snake snake[128]) {
	for (uint8_t i = 128 - gameState->numberOfDots; i < 127; i++) {
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;
	}
	switch (gameState->directon) {
		case 0:
			++snake[127].x;
			break;
		case 1:
			++snake[127].y;
			break;
		case 2:
			--snake[127].x;
			break;
		case 3:
			--snake[127].y;
			break;
	}
}

void correct_me_if_im_wrong(GameState* gameState, Snake snake[128],
			    Food* food) {
	// infinite screen looparound
	if (snake[127].x > 16) {
		snake[127].x = 1;
	}
	if (snake[127].x < 1) {
		snake[127].x = 16;
	}
	if (snake[127].y > 8) {
		snake[127].y = 1;
	}
	if (snake[127].y < 1) {
		snake[127].y = 8;
	}
}

void event(GameState* gameState, Snake snake[128], Food* food) {
	// has eaten food?
	if (snake[127].x == food->x && snake[127].y == food->y) {
		++gameState->numberOfDots;
		food->x = rand() % 16 + 1;
		food->y = rand() % 8 + 1;
		_delay_ms(500);
	}
	// dead??
	for (uint8_t i = 128 - gameState->numberOfDots; i < 127; ++i) {
		if (snake[127].y == snake[i].y && snake[127].x == snake[i].x) {
			_delay_ms(1000);
			i = 130;
			dead = 1;
		}
	}
	if (dead) {
		// death(&gameState, snake, &food);
		//initDisplay();
		gameState->numberOfDots = 3;
		gameState->directon = 0;
		snake[127].x = 9;
		snake[127].y = 4;
		snake[126].x = 8;
		snake[126].y = 4;
		snake[125].x = 7;
		snake[125].y = 4;

		food->x = rand() % 16 + 1;
		food->y = rand() % 8 + 1;
		dead = 0;
	}
}

void keypress(GameState* gameState) {
	// UP
	if (!(PIND & (1 << _UP)) && gameState->directon != 3) {
		gameState->directon = 1;
	}
	// DOWN
	if (!(PIND & (1 << _DOWN)) && gameState->directon != 1) {
		gameState->directon = 3;
	}
	// RIGHT
	if (!(PIND & (1 << _RIGHT)) && gameState->directon != 2) {
		gameState->directon = 0;
	}
	// LEFT
	if (!(PIND & (1 << _LEFT)) && gameState->directon != 0) {
		gameState->directon = 2;
	}
}
