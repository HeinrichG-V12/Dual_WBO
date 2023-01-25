/*
 * SensorFaultState.h
 *
 * Created: 23.01.2023 17:00:06
 *  Author: Heinrich
 */ 


#ifndef SENSORFAULTSTATE_H_
#define SENSORFAULTSTATE_H_

#include <stdint.h>
#include <stdbool.h>

enum class SensorFaultState
{
	OK			= 0x0
	, FAULT		= 0x1
};


#endif /* SENSORFAULTSTATE_H_ */