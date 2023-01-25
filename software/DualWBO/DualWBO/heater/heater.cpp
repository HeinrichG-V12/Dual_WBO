/*
 * heater.cpp
 *
 * Created: 23.01.2023 17:16:04
 *  Author: Heinrich
 */ 

#include "heater.h"
#include "../helpers.h"

Heater::Heater ()
{
	
	this->pid = PID();
}

void Heater::setVoltage (uint16_t voltageMillis, uint16_t systemVoltage)
{
	this->voltageMillis = voltageMillis;
	uint16_t duty = (voltageMillis == 0) ? 0 : voltage2duty_cycle(voltageMillis, systemVoltage, 256);
	setDuty(duty);
}

uint16_t Heater::getVoltage (void)
{
	return this->voltageMillis;
}

void Heater::setDuty (uint16_t duty)
{
	// nothing to do
}