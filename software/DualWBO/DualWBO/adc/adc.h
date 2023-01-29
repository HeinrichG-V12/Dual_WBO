/*
 * adc.h
 *
 * Created: 25.01.2023 17:08:44
 *  Author: Heinrich
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <stdint.h>

class Adc
{
	public:
	static Adc* getInstance();
	uint16_t readValue(uint8_t channel, uint8_t samples);

	private:
	static Adc* _instance;
	Adc();
	Adc( const Adc& );
	Adc& operator=(const Adc&);	
};



#endif /* ADC_H_ */