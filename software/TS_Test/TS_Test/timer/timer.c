/*
 * timer.c
 *
 * Created: 11.05.2022 12:30:07
 *  Author: Heinrich
 */ 

#include "timer.h"

void init_100ms_timer (void)
{
	TCNT1 = 34286;
	TCCR1A = 0x00;
	TCCR1B = (1<<CS12);  // Timer mode with 256 prescler
	TIMSK1 = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
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