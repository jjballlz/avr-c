/***************************************
 *
 * File >>_> SPI_LIB.h
 * 
 * Creation date >>_> 16.10-2019
 * Last modified >>_> Wed 16 Oct 2019 03:19:20 PM CEST
 *
 * Author >>_> gian.SANDRI
 *
 ***************************************/

#ifndef SPI_LIB_h
#define SPI_LIB_h

#include "SPI_LIB.c"


void SPI_transmit(uint8_t addr0, uint8_t instruction0, uint8_t addr1,
		  uint8_t instruction1);

#endif
