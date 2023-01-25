/*
 * pwm.c
 *
 * Created: 03.05.2022 15:23:09
 *  Author: Heinrich
 */ 

#include "pwm.h"

// pwm pins: 
// OC3A : PWM Output A for Timer/Counter3 (PE3)
// OC3B : PWM Output B for Timer/Counter3 (PE4)
// frequency = F_CPU / PRESCALER * (1 + TOP)
// frequency = 16MHz / 64 * (1 + 1023) = 16MHz / (64 * 1024) = 16 / 65536 = 244Hz
// mode 7: fast pwm, 10 bit, 0x03FF TOP, update TOP, overflow on TOP
// clear oc3a and oc3b on compare match
void pwm_init (void)
{
	TCCR3A |= (1 << WGM31)|(1 << WGM30)|(1 << COM3B1);
	TCCR3B |= (1 << WGM32)|(1 << CS31)|(1 << CS30);
	pwm_setDuty(0,0);
	pwm_setDuty(1,0);
}

void pwm_setDuty (uint8_t channel, uint16_t duty)
{
	switch (channel)
	{
		case 1:
			if (duty == 0)
			{
				TCCR3A &= ~(1 << COM3A1);
			}
			else
			{
				OCR3A = duty;
				if (!(TCCR3A & (1 << COM3A1)))
				{
					TCCR3A |= (1 << COM3A1);
				}
			}

			break;
		case 2:
			if (duty == 0)
			{
				TCCR3B &= ~(1 << COM3B1);
			}
			else
			{
				OCR3B = duty;
				if (!(TCCR3A & (1 << COM3B1)))
				{
					TCCR3A |= (1 << COM3B1);
				}
			}

			break;
	}
}
