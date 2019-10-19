/***************************************
 *
 * File >>_> max_libs.c
 *
 * Creation date >>_> 16.10-2019
 * Last modified >>_> Sat 19 Oct 2019 02:45:26 PM CEST
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

	// no scan limit
	SPI_transmit(0xB, 0xff, 0xB, 0xff);
	// turn all leds off
	for (int i = 1; i < 9; ++i) {
		SPI_transmit(i, 0x00, i, 0x00);
	}
}

void matrixWrite(GameState* gameState, Snake snake[128], Food* food) {
	// the x y values will be from 1-16(x) and 1-8(y)
	// if x is from 1-8 = first matrix(0) else 2nd(1)
	uint8_t _RR0[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t _RR1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	for (uint8_t i = 127; i >= 128-gameState->numberOfDots; --i) {
		uint8_t _x = snake[i].x;
		uint8_t _y = snake[i].y-1;
		if (_x > 8) {
			_RR0[_y] |= ( 1 << _x-9 );
		} else {
			_RR1[_y] |= ( 1 << _x-1 );
		}
	}

	if (food->x > 8) {
		_RR0[food->y-1] |= ( 1 << food->x-9 );
	}else{
		_RR1[food->y-1] |= ( 1 << food->x-1 );
	}

	for (uint8_t i = 0x1; i <= 0x8; ++i) {
		SPI_transmit(i, _RR0[i - 1], i, _RR1[i - 1]);
	}
}

