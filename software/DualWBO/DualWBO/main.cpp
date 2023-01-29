/*
 * DualWBO.cpp
 *
 * Created: 23.01.2023 16:33:34
 * Author : Heinrich
 */ 

#include <avr/io.h>

#include "sensor/sensor.h"
#include "spi/spi.h"
#include "adc/adc.h"

// https://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_Eigene_Datentypen_definieren/_Erstellen_und_Zerst%C3%B6ren
// https://www.oreilly.com/library/view/c-cookbook/0596007612/ch08s10.html
int main(void)
{
	Sensor sensor1 = Sensor();
	Spi* spi = Spi::getInstance();
	spi->spi_readWrite(0xffff);
	Adc* adc = Adc::getInstance();
	adc->readValue(0, 5);
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

