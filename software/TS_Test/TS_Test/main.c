/*
 * TS_Test.c
 *
 * Created: 03.05.2022 20:20:29
 * Author : Heinrich
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "uart/uart.h"
#include "timer/timer.h"
#include "adc/adc.h"
#include "helpers.h"

/*
https://wolles-elektronikkiste.de/timer-und-pwm-teil-2-16-bit-timer1
*/

extern uint16_t tcnt1_preload;

int16_t calculate_pump_current (uint16_t Ua, uint16_t Ua_cal);
uint16_t interpolate (int16_t ip);

uint8_t eeprom_signature[] EEMEM = "Speeduino Dual EGO Controller";
uint8_t eeprom_versionInfo[] EEMEM = "Speeduino Dual EGO Controller v0.0.1";
uint8_t eeprom_config[] EEMEM = {0x25, 0x2b, 0x93, 0x80, 0x01, 0x81, 0x01, 0x90, 0x01};

// pump current and lambda values from Bosch datasheet
// Ip * 1000
// lambda * 1000
int16_t eeprom_ip[] EEMEM = {-2000, -1602, -1243, -927, -800, -652, -405, -183, -106, -40, 0, 15, 97, 193, 250, 329, 671, 938, 1150, 1385, 1700, 2000, 2150, 2250};
uint16_t eeprom_lambda[] EEMEM = {650, 700, 750, 800, 822, 850, 900, 950, 970, 990, 1003, 1010, 1050, 1100, 1132, 1179, 1429, 1701, 1990, 2434, 3413, 5391, 7506, 10119};

	
uint8_t signature[sizeof(eeprom_signature)];
uint8_t versionInfo[sizeof(eeprom_versionInfo)];
uint8_t controllerSettings[sizeof(eeprom_config)];

int16_t ip_values[sizeof(eeprom_ip)];
uint16_t lambda_values[sizeof(eeprom_lambda)];

uint8_t liveData[32];

uint8_t rxBuffer[32];

uint8_t multiByteCommandBuffer[32];

uint16_t tmp;

volatile uint16_t pwm1 = 128;
volatile uint16_t pwm2 = 700;
volatile uint16_t mainLoopsPerSecond = 0;
volatile uint16_t adc_value = 0;

uint8_t string[] = "Hallo Welt, das ist ein Interrupttest!\r\n";

typedef struct {
	// first byte in the config:
	uint8_t isCanEnabled : 1;
	uint8_t canSpeed : 2;
	uint8_t interfaceActivation : 1;
	uint8_t isCANDebugEnabled : 1;
	uint8_t use29bitIdentifier :1;
	uint8_t amplificationFactor :1;
	uint8_t unused1 : 1;

	// second byte in the config:
	uint8_t isChannel1Enabled : 1;
	uint8_t isChannel2Enabled : 1;
	uint8_t channel1OutputMode : 2;
	uint8_t channel2OutputMode : 2;
	uint8_t channel1AnalogOutputMode : 1;
	uint8_t channel2AnalogOutputMode : 1;

	// third by in the config:
	uint8_t stoich_ratio;

	uint16_t channel1CANid;
	uint16_t channel2CANid;
	uint16_t debugMessageID;
} tConfig;

typedef enum
{
	can_125
	, can_250
	, can_500
	, can_1000

} tCANSpeed;

typedef enum {
	CJ125_E_SHORTCIRCUITGND
	, CJ125_E_NOPOWER
	, CJ125_E_SHORTCIRCUITBAT
	, CJ125_OK
} tCJ125_status;

typedef struct {
	tCJ125_status status;
	uint16_t Ua_cal;
	uint16_t Ua;
	uint16_t Ur_cal;
	uint16_t Ur;
	int16_t Ip;	
} tSensor;

tConfig* configuration;

tSensor sensor1;

#define SENSOR_SHUNT	61.9

ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	//PORTB ^= (1 << PB7);	// pb7 ist high

	liveData[0]++;
	PORTB ^= (1 << PB7);
	
	liveData[30] = low(mainLoopsPerSecond);
	liveData[31] = high(mainLoopsPerSecond);
	
	mainLoopsPerSecond = 0;
	
	TCNT1 = tcnt1_preload;   // for 1 sec at 16 MHz
}


ISR(USART2_RX_vect)
{
	uint8_t data;
	
	data = UDR2;
	
	switch (data)
	{
		case 'A':
		PORTB ^= (1 << PB7);	// pb7 ist high
		break;
		case 'F':
		uart2_sendS((uint8_t*) string, sizeof(string)-1);
		break;
		
		case 'V':	// reading controller settings
		uart2_sendS((uint8_t*) controllerSettings, sizeof(controllerSettings));
		break;
		
		
		case 'L':
		tmp = adc_value;
		
		// sensor1.Ip = ((sensor1.Ua-sensor1.Ua_cal)/(619*8))*1000;
		
		uart2_sendS((uint8_t*) adc_value, sizeof(adc_value));
		break;
	}
}



int main(void)
{
	uart_init();
	uart2_sendS((uint8_t*) "reboot!", 7);
	adc_init();
	
	DDRB |= (1 << PB7);		// pb7 ist ausgang
	// PORTB |= (1 << PB7);	// pb7 ist high

	eeprom_read_block((void*)signature, (const void*) eeprom_signature, sizeof(eeprom_signature));
	eeprom_read_block((void*)versionInfo, (const void*) eeprom_versionInfo, sizeof(eeprom_versionInfo));
	eeprom_read_block((void*)controllerSettings, (const void*) eeprom_config, sizeof(eeprom_config));
	
	eeprom_read_block((void*)ip_values, (const void*) eeprom_ip, sizeof(eeprom_ip));
	eeprom_read_block((void*)lambda_values, (const void*) eeprom_lambda, sizeof(eeprom_lambda));
	
 	configuration = (tConfig*)controllerSettings;
	
	init_1s_timer();
	
	uint16_t blah;
		
	sei();
	
	sensor1.status = CJ125_OK;
	sensor1.Ua_cal = 1500;

	uint8_t offset;
	uint8_t value;
	uint8_t pageIdentifier = 0;
	
	liveData[1] = 138;
	
	liveData[6] = low(pwm1);
	liveData[7] = high(pwm1);
	
	liveData[8] = low(pwm2);
	liveData[9] = high(pwm2);
	
    /* Replace with your application code */
    while (1) 
    {
		switch (uart_getData())
		{
			case 'F':	// serial protocol version request
				uart_sendS((uint8_t*) "001", 3);
				break;
			case 'Q':	// code version
				uart_sendS((uint8_t*) signature, sizeof(signature));
				break;
				
			case 'S':	// signature, has to be the same like in ini-file
				uart_sendS((uint8_t*) versionInfo, sizeof(versionInfo)-1);
				break;
				
			case 'V':	// reading controller settings
				if (pageIdentifier == 0x01)
				{
					uart_sendS((uint8_t*) controllerSettings, sizeof(controllerSettings));										
				}
				
				if (pageIdentifier == 0x02)
				{
					uart_sendS((uint8_t*) ip_values, 48);
					uart_sendS((uint8_t*) lambda_values, 48);
				}
				
				break;
				
			case 'A':	// reading live data
				adc_value = adc_read(3);
				sensor1.Ua = adc2voltage_mili(adc_value);
				liveData[12] = low(sensor1.Ua);
				liveData[13] = high(sensor1.Ua);
				
				sensor1.Ip = calculate_pump_current(sensor1.Ua, sensor1.Ua_cal);
								
				liveData[18] = low(sensor1.Ip);
				liveData[19] = high(sensor1.Ip);
				
				blah = interpolate(sensor1.Ip);
				
				liveData[2] = low(blah);
				liveData[3] = high(blah);
								
				uart_sendS((uint8_t*) liveData, sizeof(liveData));
				break;
				
			case 'W':	// update controller config string
				while (!uart_hasData()) {};	// wait for offset
				offset = uart_getData();
				while (!uart_hasData()) {};	// wait for value
				value = uart_getData();
				controllerSettings[offset] = value;
				break;
				
			case 'E':	// execute button command, this command is always 3 byte long
				multiByteCommandBuffer[0] = 'E';
				
				while (!uart_hasData()) {};
				multiByteCommandBuffer[1] = uart_getData();
			
				while (!uart_hasData()) {};
				multiByteCommandBuffer[2] = uart_getData();
				
				uart2_sendS((uint8_t*) multiByteCommandBuffer, 3);
				break;
				
			case 'B':	// push controller config string to eeprom
				eeprom_update_block((const void*) &controllerSettings, (void*) eeprom_config, sizeof(eeprom_config));
				break;
				
			case 'P':
				while (!uart_hasData()) {};
				pageIdentifier = uart_getData();
				break;								
		}
		
		mainLoopsPerSecond++;
    }
}

int16_t calculate_pump_current (uint16_t Ua, uint16_t Ua_cal)
{	
	return (((int16_t)Ua - (int16_t)Ua_cal) / (SENSOR_SHUNT * 8) * 1000);
}

uint16_t interpolate (int16_t ip)
{
	uint16_t y = 0;
	uint8_t counter = 0;
	
	float gain, offset;
	
	// check against the both ends
	if (ip <= ip_values[0]) 
	{
		y = lambda_values[0];
	}
	
	if (ip >= ip_values[23])
	{
		y = lambda_values[23];
	}
	
	while ((y == 0) && (counter < 23))
	{
		// exists an exact value?
		if ( ip_values[counter] == ip)
		{
			y = lambda_values[counter];
		}
		
		// ip value is between two values
		else if ((ip_values[counter] <= ip) && (ip <= ip_values[counter + 1]))
		{
			gain = (float) (lambda_values[counter+1] - lambda_values[counter]) / (ip_values[counter + 1] -  ip_values[counter]);
			
			offset = (lambda_values[counter+1] - (ip_values[counter + 1] * gain));
			
			y = (uint16_t) ((ip * gain) + offset);
		}
		counter++;
	}
	
	return y;
}