/*
 * pwm.h
 *
 * Created: 03.05.2022 15:22:10
 *  Author: Heinrich
 */ 


#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void pwm_init (void);
void pwm_setDuty (uint8_t channel, uint16_t duty);



#endif /* PWM_H_ */