/*
 * probe.h
 *
 * Created: 05.05.2022 10:43:26
 *  Author: Heinrich
 */ 


#ifndef PROBE_H_
#define PROBE_H_

typedef enum
{
	INIT
	, NO_PROBE
	, WAIT_FOR_START
	, CONDENSATE
	, PREHEATING
	, CALIBRATE
	, RUNNING
	, ERROR
} tProbeState;

typedef struct {
	uint8_t adc_channel;
	uint8_t adc_samples;
	uint16_t UA;
	uint16_t UA_reference;
	uint16_t UR;
	uint16_t UR_reference;
	uint16_t PWM;
	
	tProbeState State;
} tSensor;

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../cj125/cj125.h"

void update_probe_data (tSensor sensor);

#endif /* PROBE_H_ */