/*
 * ecu.h
 *
 * Created: 05.05.2022 11:52:31
 *  Author: yf89386
 */ 


#ifndef ECU_H_
#define ECU_H_

#include <avr/eeprom.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "../helpers.h"

#define ECU_LABEL_OFFSET	0
#define ECU_LABEL_SIZE		32

#define ECU_CONFIG_OFFSET	33

/*
typedef enum {
	can125
	, can250
	, can500
	, can1000
} tCanSpeed;

typedef enum {
	CAN
	, Input	
}tInterfaceActivation;

typedef enum {
	analog_output
	, CAN_output
	, analog_CAN_output
}tOutputMode;

typedef enum {
	wideband
	, narrowband	
}tAnalogOutputMode;

typedef struct {
	bool isCanActive;
	tCanSpeed canSpeed;
	tInterfaceActivation tIntActivation;
	bool isCANDebugEnabled;
	bool isChannel1Enabled;
	bool isChannel2Enabled;
	tOutputMode channel1OutputMode;
	tOutputMode channel2OutputMode;
	tAnalogOutputMode channel1AnalogOutputMode;
	tAnalogOutputMode channel2AnalogOutputMode;
	uint16_t channel1CanID;
	uint16_t channel2CanID;	
} tEcuConfig;

*/

typedef struct {
	uint8_t isCanActive : 1;
	uint8_t canSpeed : 2;
	uint8_t IntActivation :1;
	uint8_t isCANDebugEnabled : 1;
	uint8_t unused1 : 3;
	
	uint8_t isChannel1Enabled : 1;
	uint8_t isChannel2Enabled : 1;
	uint8_t channel1OutputMode : 2;
	uint8_t channel2OutputMode : 2;
	uint8_t channel1AnalogOutputMode : 1;
	uint8_t channel2AnalogOutputMode : 1;
	
	uint8_t stoich_ratio;
	
	uint16_t channel1CanID;
	uint16_t channel2CanID;
} tEcuConfig;

// very interesting: 
// https://www.microchip.com/forums/FindPost/1126733, post #4
// https://microchipdeveloper.com/tls2101:bit-fields

#endif /* ECU_H_ */


