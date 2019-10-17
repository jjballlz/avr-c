/***************************************
 *
 * File >>_> max_libs.c
 *
 * Creation date >>_> 16.10-2019
 * Last modified >>_> Thu 17 Oct 2019 12:06:56 PM CEST
 *
 * Author >>_> gian.SANDRI
 *
 ***************************************/

void initDisplay(void) {
	// turn off screen test
	SPI_transmit(0xF, 0x00, 0xF, 0x00);

	// turn "off" shutdown register
	SPI_transmit(0xC, 0x01, 0xC, 0x01);

	// no decode-mode
	SPI_transmit(0x9, 0x00, 0x9, 0x00);

	// set led intesity low
	SPI_transmit(0xA, 0x00, 0xA, 0x00);
	// turn all leds off
	for (int i = 1; i < 9; ++i) {
		SPI_transmit(i, 0x00, i, 0x00);
	}
}

void matrixWrite(GameState* gameState, Snake* snake[127]) {
	// the x y values will be from 1-16(x) and 1-8(y)
	// if x is from 1-8 = first matrix else 2nd
	// we are only writing 1s, to turn it off, that will be a specific
	// funtion
	uint8_t _RR0[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	uint8_t _RR1[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	for (uint8_t i = 127; i >= (128 - gameState->numberOfDots); --i) {
		uint8_t _x = snake[i]->x;
		uint8_t _y = snake[i]->y;
		if (_x > 8) {
			_x = _x - 8;
			_RR1[_y] |= (1 << _x);
		} else {
			_RR0[_y] |= (1 << _x);
		}
	}

	for (uint8_t i = 1; i <= 8; ++i) {
		SPI_transmit(i, _RR0[i-1], i, _RR1[i-1]);
	}
}

