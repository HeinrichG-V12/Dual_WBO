/*
 * ecu.c
 *
 * Created: 05.05.2022 11:52:41
 *  Author: Heinrich
 */ 

#include "ecu.h"
#include <avr/eeprom.h>

tEcuConfig ecuConfig;
uint8_t ecuLabel[ECU_LABEL_SIZE];

uint8_t signature[] EEMEM = "speeduino Dual WBO Controller";
uint8_t banner[] EEMEM = "speeduino Dual WBO Controller V0.0.1";
uint8_t config[] EEMEM = "000000000";

void loadECUconfig (void)
{
	uint8_t configuration[10];
	
	memset((void*)&ecuConfig, 0, sizeof(ecuConfig));
	
	eeprom_read_block((void*)ecuLabel, (const void*)ECU_LABEL_OFFSET, sizeof(ecuLabel));
	eeprom_read_block((void*)&ecuConfig, (const void*)ECU_CONFIG_OFFSET, sizeof(ecuConfig));
	
}