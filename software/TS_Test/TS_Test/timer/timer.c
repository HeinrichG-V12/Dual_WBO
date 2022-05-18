/*
 * timer.c
 *
 * Created: 11.05.2022 12:30:07
 *  Author: Heinrich
 */ 

#include "timer.h"

uint16_t tcnt1_preload = 3036;

void init_1s_timer (void)
{
	// 1s: prescale = 256 and preload = 3036
	// 1s: prescale = 1024 and preload = 49911
	TCNT1 = tcnt1_preload;
	TCCR1A = 0x00;
	TCCR1B |= (1<<CS12);		// Timer mode with 1024 prescler
	TIMSK1 = (1 << TOIE1);		// Enable timer1 overflow interrupt(TOIE1)
}

/*
ISR(TIMER0_OVF_vect)
{
	DDRB ^= (1 << PB7);

	pwm1++;
	
	if (pwm1 == 1023)
	{
		pwm1 = 0;
	}
	
	pwm2--;
	
	if (pwm2 == 0)
	{
		pwm2 = 1023;
	}
	
	
	TCNT0 = 178;
}
*/