/*
 * adc.cpp
 *
 * Created: 25.01.2023 17:09:17
 *  Author: Heinrich
 */ 

#include "adc.h"

// Define the static Singleton pointer
Adc* Adc::_instance = nullptr;

Adc::Adc()
{
	// init adc...
}

Adc* Adc::getInstance()
{
	if( _instance == nullptr )
	_instance = new Adc();
	return _instance;
}

uint16_t Adc::readValue(uint8_t channel, uint8_t samples)
{
	return 0;
}