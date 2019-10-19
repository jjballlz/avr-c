/***************************************
 *
 * File >>_> SPI_LIB.c
 *
 * Creation date >>_> 16.10-2019
 * Last modified >>_> Fri 18 Oct 2019 05:01:42 PM CEST
 *
 * Author >>_> gian.SANDRI
 *
 ***************************************/

void SPI_init(void) {
	/*********************************
	 *     SPI INIT -- MASTER
	 *     ==================
	 * MOSI      ~> output
	 * MISO      ~> input
	 * SS        ~> output (SET HIGH)
	 * SCK       ~> output
	 * MODE      ~> 0 (default)
	 * PRESCALER ~> f_clock/128
	 * BIT DIR   ~> MSB first
	 *********************************/
	DDRB = (1 << _SS) | (1 << _MOSI) | (1 << _SCK);
	PORTB |= (1 << _SS);

	SPCR = (1 << SPE) | (1 << MSTR);
	SPCR |= (1 << SPR0) | (1 << SPR1);
}

void SPI_transmit(uint8_t addr0, uint8_t instruction0, uint8_t addr1,
		  uint8_t instruction1) {
	SPDR = addr1;
	PORTB &= ~(1 << _SS);
	while (!(SPSR & (1 << SPIF)))
		;

	SPDR = instruction1;
	while (!(SPSR & (1 << SPIF)))
		;
	SPDR = addr0;
	while (!(SPSR & (1 << SPIF)))
		;

	SPDR = instruction0;
	while (!(SPSR & (1 << SPIF)))
		;

	PORTB |= (1 << _SS);
}
