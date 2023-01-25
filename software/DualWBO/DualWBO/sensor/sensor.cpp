/*
 * sensor.cpp
 *
 * Created: 23.01.2023 16:50:55
 *  Author: Heinrich
 */ 

#include "sensor.h"

Sensor::Sensor (uint8_t amplificationFactor)
{
	this->Amplification = amplificationFactor;
	this->sensorStatus = SensorStatus::ERROR;
	this->sensorFaultState = SensorFaultState::OK;
	this->sensorDetectedStatus = SensorDetectedStatus::BOSCH_LSU49;
	this->heater = Heater();
}

void Sensor::update_ua (uint16_t ua_millis)
{
	this->Ua = ua_millis;
	// this->Ip = calculate_ip(this->Ua_ref, this->Ua, this->Amplification);
}

void Sensor::shutdown (void)
{
	this->sensorStatus = SensorStatus::RESET;
	this->heater.setVoltage(0, this->SystemVoltage);
	this->Ua = 0;
	this->Ur = 0;
	this->Ip = 0;
	this->Lambda = 0;
}