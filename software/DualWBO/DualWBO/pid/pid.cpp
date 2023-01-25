/*
 * pid.cpp
 *
 * Created: 23.01.2023 16:41:18
 *  Author: Heinrich
 */ 

#include "pid.h"

PID::PID(float pGain, float iGain, float dGain, int16_t pwmMin, int16_t pwmMax)
{
	this->pGain = pGain;
	this->iGain = iGain;
	this->dGain = dGain;
	this->pwmMin = pwmMin;
	this->pwmMax = pwmMax;
}

uint16_t PID::calculate(uint16_t referenceValue, uint16_t measuredValue, bool inverted)
{
	float pTerm = 0, iTerm = 0, dTerm = 0;
	// calculation error:
	int16_t error = (int16_t) referenceValue - (int16_t) measuredValue;
	int16_t position = (int16_t) measuredValue;
	
	// calculate p-term;
	if (inverted)
	{
		pTerm = -this->pGain * error;
		} else {
		pTerm = this->pGain * error;
	}
	
	//Calculate the integral state
	this->iState += error;
	
	// check limits of iState
	if (this->iState > this->iMax) this->iState = this->iMax;
	if (this->iState < this->iMin) this->iState = this->iMin;
	
	//Calculate the integral term.
	if (inverted)
	{
		iTerm = -this->iGain * this->iState;
		} else {
		iTerm = this->iGain * this->iState;
	}
	
	//Calculate the derivative term.
	if (inverted)
	{
		dTerm = -this->dGain * (this->dState - position);
		} else {
		dTerm = this->dGain * (this->dState - position);
	}
	this->dState = position;
	
	//Calculate regulation (PI).
	int16_t RegulationOutput = pTerm + iTerm + dTerm;
	
	// check limits of pwm here....
	
	if (RegulationOutput > this->pwmMax)
	{
		RegulationOutput = this->pwmMax;
	}
	
	if (RegulationOutput < this->pwmMin)
	{
		RegulationOutput = this->pwmMin;
	}
	
	return  (uint16_t) RegulationOutput;
}