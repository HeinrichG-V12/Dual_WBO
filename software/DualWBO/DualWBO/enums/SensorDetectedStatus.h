/*
 * SensorDetectedStatus.h
 *
 * Created: 23.01.2023 17:00:53
 *  Author: Heinrich
 */ 


#ifndef SENSORDETECTEDSTATUS_H_
#define SENSORDETECTEDSTATUS_H_

#include <stdint.h>
#include <stdbool.h>

enum class SensorDetectedStatus
{
	Reserved1		= 0x1
	, BOSCH_LSU49	= 0x2
	, Reserved2		= 0x4
	, Reserved3		= 0x8
};


#endif /* SENSORDETECTEDSTATUS_H_ */