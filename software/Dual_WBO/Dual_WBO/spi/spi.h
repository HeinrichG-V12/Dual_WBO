/*
 * spi.h
 *
 * Created: 12.12.2021 20:01:16
 *  Author: Heinrich
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <stdint.h>

void spi_init (void);
uint16_t spi_read_write (uint16_t data);

#endif /* SPI_H_ */