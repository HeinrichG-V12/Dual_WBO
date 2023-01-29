/*
 * spi.cpp
 *
 * Created: 25.01.2023 17:23:31
 *  Author: Heinrich
 */ 

#include "spi.h"

// Define the static Singleton pointer
Spi* Spi::_instance = nullptr;


Spi::Spi()
{
	int i = 10;
}


Spi* Spi::getInstance() {
	if (_instance == nullptr) {
		_instance = new Spi();
	}
	return(_instance);
}