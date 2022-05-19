/*
 * adc.h
 *
 * Created: 18.05.2022 12:43:55
 *  Author: Heinrich
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <stdint.h>

void adc_init (void);
uint16_t adc_read (uint8_t channel);
uint16_t adc_read_avg (uint8_t channel, uint8_t samples);


#endif /* ADC_H_ */