/*
 * pid.h
 *
 * Created: 23.01.2023 16:35:06
 *  Author: Heinrich
 */ 


#ifndef PID_H_
#define PID_H_

#include <stdint.h>
#include <stdbool.h>

class PID {
	public:
		PID (float pGain = 5, float iGain = 0.8, float dGain = 3.2, int16_t pwmMin = 0, int16_t pwmMax = 240);
		uint16_t calculate (uint16_t referenceValue, uint16_t measuredValue, bool inverted);
	
	private:
		float pGain;
		float iGain;
		float dGain;
		int16_t iState;
		int16_t dState;
		int16_t iMin;
		int16_t iMax;
		int16_t pwmMin;
		int16_t pwmMax;
	};



#endif /* PID_H_ */