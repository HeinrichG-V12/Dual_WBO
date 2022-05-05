/*
 * adc.c
 *
 * Created: 03.05.2022 11:55:05
 *  Author: Heinrich
 */ 


#include "adc.h"

void adc_init (void)
{
	// adc enable, prescaler 128 (125khz)
	ADCSRA |= (1 << ADEN)|(1 << ADPS2)|(1 << ADPS2)|(1 << ADPS0);
}

uint16_t adc_read (uint8_t channel)
{
	ADMUX |= (ADMUX & ~(0x1F)) | (channel & 0x1F);
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC) );
		
	return ADCW;
}

uint16_t adc_read_avg (uint8_t channel, uint8_t samples)
{
	uint32_t buf = 0;
	
	for (uint8_t i = 0; i < samples; i++)
	{
		buf += adc_read(channel);
	}
	
	return (uint16_t) (buf / samples);
}