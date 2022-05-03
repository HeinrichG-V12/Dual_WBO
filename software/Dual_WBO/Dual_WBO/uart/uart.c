/*
 * uart.c
 *
 * Created: 03.05.2022 11:34:23
 *  Author: Heinrich
 */ 

#include "uart.h"

void uart_init (void)
{
	//init uart 1 with 115200, 8n1
	
	UBRR1 = UBRR_115k;
	
	UCSR1B |= (1 << RXCIE1)|(1 << RXEN1)|(1 << TXEN1);
	UCSR1C |= (1 << UCSZ11)|(1 << UCSZ10);	
}

void uart_sendC (uint8_t data)
{
	while (!(UCSR1A & (1 << UDRE1)));
	UDR1 = data;
}

void uart_sendString (uint8_t *data, uint8_t length)
{
	uint8_t actPos = 0;
	
	while (actPos <= length)
	{
		uart_sendC(data[actPos]);
		actPos++;		
	}
}

ISR(USART1_RX_vect)
{
	//tue was
}