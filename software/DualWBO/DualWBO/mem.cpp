/*
 * mem.cpp
 *
 * Created: 29.01.2023 23:02:12
 *  Author: Heinrich
 */ 

#include <stdlib.h>

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};
	
// And last thing, if you use pure virtual functions you must define another function:
//extern "C" void __cxa_pure_virtual(void);

void * operator new(size_t size)
{
	return malloc(size);
}

void operator delete(void * ptr)
{
	free(ptr);
}