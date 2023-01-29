/*
 * heater.h
 *
 * Created: 23.01.2023 17:15:53
 *  Author: Heinrich
 */ 


#ifndef HEATER_H_
#define HEATER_H_

#include <avr/io.h>
#include "../pid/pid.h"

class Heater {
	public:
		Heater();
		void setVoltage (uint16_t voltageMillis, uint16_t systemVoltage);
		uint16_t getVoltage (void);
	
	private:
		void setDuty (uint16_t duty);
		uint16_t voltageMillis;
		PID pid;
};



#endif /* HEATER_H_ */