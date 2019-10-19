/***************************************
 *
 * File >>_> splashes.c
 *
 * Creation date >>_> 19.10-2019
 * Last modified >>_> Sat 19 Oct 2019 02:36:19 PM CEST
 *
 * Author >>_> gian.SANDRI
 *
 ***************************************/

void death(GameState* gameState, Snake snake[128], Food* food) {
	uint8_t _RR0[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t _RR1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	for (uint8_t i = 0; i < 16; ++i) {
		for (uint8_t j = 8; j < 0; --j) {
			if (i > 8) {
				_RR0[j] |= (1 << i - 8);
				for (uint8_t i = 0x1; i <= 0x8; ++i) {
					SPI_transmit(i, _RR0[i - 1], i,
						     _RR1[i - 1]);
					_delay_ms(100);
				}
			} else {
				_RR1[j] |= (1 << i);
				for (uint8_t i = 0x1; i <= 0x8; ++i) {
					SPI_transmit(i, _RR0[i - 1], i,
						     _RR1[i - 1]);
					_delay_ms(100);
				}
			}
		}
	}
}
