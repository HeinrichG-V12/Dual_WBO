/*
 * SensorStatus.h
 *
 * Created: 23.01.2023 16:57:25
 *  Author: Heinrich
 */ 


#ifndef SENSORSTATUS_H_
#define SENSORSTATUS_H_

#include <stdint.h>
#include <stdbool.h>

enum class SensorStatus
	{
		RESET							= 0x0
		, WARMING_UP					= 0x1
		, STABILIZING					= 0x2
		, READING_NERST_PUMP_IMPEDANCE	= 0x3
		, EQUALIZING					= 0x4
		, READING_RCAL_VALUE			= 0x5
		, RUN							= 0x6
		, OVERHEAT						= 0x7
		, OVERCOOL						= 0x8
		, HEATER_SHORT_CIRCUIT			= 0x9
		, HEATER_OPEN_CIRCUIT			= 0xA
		, START_FAC						= 0xB	// FAC: FreeAirCalibration: since we are using LSU4.9 it is not necessary
		, PERFORMING_FAC				= 0xC	// FAC: FreeAirCalibration: since we are using LSU4.9 it is not necessary
		, DETECTING_SENSOR				= 0xD
		, READING_JUNCTION_IMPEDANCE	= 0xE
		, EVAP_START_UP					= 0xF
		, DETERMINING_SENSOR_TYPE		= 0x10
		, PREPARING_TO_RUN				= 0x11
		, SAVE_SENSOR					= 0x12
		, NEED_NEW_FAC					= 0x13	// FAC: FreeAirCalibration: since we are using LSU4.9 it is not necessary
		, ERROR							= 0x14
	};

#endif /* SENSORSTATUS_H_ */