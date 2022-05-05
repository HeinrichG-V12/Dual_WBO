/*
 * ecu.c
 *
 * Created: 05.05.2022 11:52:41
 *  Author: Heinrich
 */ 

#include "ecu.h"

tEcuConfig ecuConfig;
uint8_t ecuLabel[ECU_LABEL_SIZE];

void loadECUconfig (void)
{
	memset((void*)&ecuConfig, 0, sizeof(ecuConfig));
	
	eeprom_read_block((void*)ecuLabel, (const void*)ECU_LABEL_OFFSET, sizeof(ecuLabel));
	eeprom_read_block((void*)&ecuConfig, (const void*)ECU_CONFIG_OFFSET, sizeof(ecuConfig));
}