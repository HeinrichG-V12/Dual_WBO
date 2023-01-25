/*
 * sensor.h
 *
 * Created: 23.01.2023 16:33:56
 *  Author: Heinrich
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_

#include "../enums/SensorStatus.h"
#include "../enums/SensorDetectedStatus.h"
#include "../enums/SensorFaultState.h"
#include "../heater/heater.h"

class Sensor {
	public:
		Sensor (uint8_t amplificationFactor = 8);
		void shutdown ();
		void update_ua (uint16_t ua_millis);
		
	
	private:
		uint8_t Signature = 0;
		uint16_t Shunt = 61900;
		uint8_t Amplification = 8;
		uint16_t Ua_ref = 0;
		uint16_t Ur_ref = 0;
		uint16_t Ur_ref_raw = 0;
		uint16_t Ua = 0;
		uint16_t Ur = 0;
		int16_t Ip = 0;
		uint16_t Lambda = 0;
		uint16_t O2 = 0;
		uint16_t SystemVoltage = 0;
		bool SystemVoltageOK = true;
		uint8_t diagRegister = 0;
		SensorStatus sensorStatus;
		SensorDetectedStatus sensorDetectedStatus;
		SensorFaultState sensorFaultState;
		Heater heater;
	};




#endif /* SENSOR_H_ */