/*
 * spi.h
 *
 * Created: 25.01.2023 17:23:40
 *  Author: Heinrich
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <stdint.h>

class Spi
{
	public:
	static Spi* getInstance();
	uint16_t spi_readWrite(uint16_t data);

	private:
	static Spi* _instance;
	Spi();
	Spi(const Spi&);
	Spi& operator=(const Spi&);
};

#endif /* SPI_H_ */