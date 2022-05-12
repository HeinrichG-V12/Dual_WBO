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

#include "uart/uart.h"
#include "timer/timer.h"

uint8_t eeprom_signature[] EEMEM = "speeduino_ Dual WBO Controller";
uint8_t eeprom_versionInfo[] EEMEM = "Dual WBO Controller 0.0.1";
uint8_t eeprom_config[] EEMEM = {0x02, 0x03, 0x93, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint8_t liveData[28];
uint8_t controllerSettings[9];

uint8_t rxBuffer[32];

uint8_t multiByteCommandBuffer[32];

volatile uint16_t pwm1 = 128;
volatile uint16_t pwm2 = 700;

ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	PORTB ^= (1 << PB7);	// pb7 ist high
	liveData[0] += 1;
	
	if ( liveData[0] == 170)
	{
		liveData[0] = 100;
	}
	
	liveData[2]++;
	
	if (liveData[2] == 130)
	{
		liveData[2] = 68;
	}

	liveData[27]++;
	
	if (liveData[27] == 254)
	{
		liveData[27] = 0;
	}
	
	
	TCNT1 = 34286;   // for 1 sec at 16 MHz
}


int main(void)
{
	DDRB |= (1 << PB7);		// pb7 ist ausgang
	PORTB |= (1 << PB7);	// pb7 ist high
	
	
	uint8_t signature[sizeof(eeprom_signature)];
	uint8_t versionInfo[sizeof(eeprom_versionInfo)];
	uint8_t controllerSettings[sizeof(eeprom_config)];
	
	eeprom_read_block((void*)signature, (const void*) eeprom_signature, sizeof(eeprom_signature));
	eeprom_read_block((void*)versionInfo, (const void*) eeprom_versionInfo, sizeof(eeprom_versionInfo));
	eeprom_read_block((void*)controllerSettings, (const void*) eeprom_config, sizeof(eeprom_config));
	
	uart_init();
	init_100ms_timer();
		
	sei();

	uint8_t offset;
	uint8_t value;
	
	liveData[0] = 127;
	liveData[1] = 100;
	liveData[2] = 92;
	
	liveData[3] = (uint8_t)(pwm1 & 0xFF);
	liveData[4] = (uint8_t)(pwm1 >> 8);
	
	liveData[5] = (uint8_t)(pwm2 & 0xFF);
	liveData[6] = (uint8_t)(pwm2 >> 8);
	
	liveData[23] = 0;

	
    /* Replace with your application code */
    while (1) 
    {
		switch (uart_getData())
		{
			case 'F':	// serial protocol version request
				uart_sendS((uint8_t*) "001", 3);
				break;
			case 'Q':	// code version
				uart_sendS((uint8_t*) signature, sizeof(signature)-1);
				break;
				
			case 'S':	// signature, has to be the same like in ini-file
				uart_sendS((uint8_t*) versionInfo, sizeof(versionInfo)-1);
				break;
				
			case 'V':	// reading controller settings
				uart_sendS((uint8_t*) controllerSettings, sizeof(controllerSettings));
				break;
				
			case 'A':	// reading live data
				uart_sendS((uint8_t*) liveData, sizeof(liveData));
				break;
				
			case 'W':	// update controller config string
				while (!uart_hasData()) {};	// wait for offset
				offset = uart_getData();
				
				while (!uart_hasData()) {};	// wait for value
				value = uart_getData();
				
				controllerSettings[offset] = value;
				
				break;
				
			case 'E':	// execute button command
				multiByteCommandBuffer[0] = 'E';
				while (!uart_hasData()) {};
				multiByteCommandBuffer[1] = uart_getData();
			
				while (!uart_hasData()) {};
				multiByteCommandBuffer[2] = uart_getData();
				
				uart2_sendS((uint8_t*) multiByteCommandBuffer, 3);
				break;
				
				
			case 'B':	// push controller config string to eeprom
				eeprom_update_block((const void*) &controllerSettings, (void*) eeprom_config, sizeof(eeprom_config));
				uart2_sendS((uint8_t*) multiByteCommandBuffer, 3);
				uart2_sendS((uint8_t*) "\r\n", 2);
				break;
		}
    }
}

