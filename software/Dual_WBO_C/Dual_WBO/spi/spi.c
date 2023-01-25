/*
 * spi.c
 *
 * Created: 12.12.2021 20:01:53
 *  Author: Heinrich
 */ 

#include "spi.h"
#include "../helpers.h"

void spi_init (void)
{
	// enable spi, 2MHz (div 128), master, mode1 (cpol 0, cpha 1)
	SPCR |= (1 << SPE)|(0 << DORD)|(1 << MSTR)|(0 << CPOL)|(1 << CPHA)|(1 << SPR1)|(1 << SPR0);
}

uint16_t spi_read_write (uint16_t data)
{
	uint8_t byte1, byte2;
	
	SPDR = (data >> 8);
	while(!(SPSR & (1<<SPIF)));
	byte1 = SPDR;
	byte1 &= ~((1 << 7)|(1 << 6));	// clear two most significant bits in control byte because of don't care, cj125 manual, page 16
	SPDR = (data & 0xFF);
	while(!(SPSR & (1<<SPIF)));
	byte2 = SPDR;
	
	return make_u16t (byte1, byte2);
}