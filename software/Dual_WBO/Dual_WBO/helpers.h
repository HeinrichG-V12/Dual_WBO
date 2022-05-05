/*
 * helpers.h
 *
 * Created: 12.12.2021 20:04:45
 *  Author: Heinrich
 */ 


#ifndef HELPERS_H_
#define HELPERS_H_

#include <stdbool.h>

static __inline uint16_t __bswap_16(uint16_t __x)
{
	return (__x << 8)|(__x >> 8);
}

static __inline uint16_t __make_u16t(uint8_t __x1, uint8_t __x2)
{
	// return (uint16_t)((__x2 << 8) + (__x1 & 0x00ff));
	return ((uint16_t) __x1 << 8) | __x2;
}

static __inline float __adc2voltage(uint16_t __v)
{
	return ((float) __v * 5UL / 1024UL );
}

static __inline uint16_t __adc2voltage_mili(uint16_t __v)
{
	return ((uint16_t) __v * 5000UL / 1024UL );
}

static __inline bool __isSet(uint8_t __x1, uint8_t __x2)
{
	return (__x1 & ( 1 << __x2));
}

#define bswap_16(x) __bswap_16(x)
#define make_u16t(x1,x2) __make_u16t(x1, x2)
#define adc2voltage(adc) __adc2voltage(adc)
#define adc2voltage_mili(adc) __adc2voltage_mili(adc)
#define isSet(x1, x2) __isSet(x1, x2)

#define Min( a, b ) (a < b) ? a : b
#define Max( a, b ) (a > b) ? a : b


#endif /* HELPERS_H_ */