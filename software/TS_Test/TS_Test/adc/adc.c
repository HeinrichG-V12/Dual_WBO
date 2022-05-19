/*
 * adc.c
 *
 * Created: 18.05.2022 12:44:26
 *  Author: Heinrich
 */ 

#include "adc.h"

void adc_init (void)
{
	ADMUX = (1 << REFS0);		// AVCC with external cap on aref pin
	ADCSRA = (1 << ADEN)|(1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2); // adc enable, prescaler 128
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