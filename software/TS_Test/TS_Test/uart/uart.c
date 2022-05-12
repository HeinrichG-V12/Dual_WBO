/*
 * uart.c
 *
 * Created: 03.05.2022 20:21:19
 *  Author: Heinrich
 */ 

#include "uart.h"

uint8_t string[] = "Hallo Welt, das ist ein Interrupttest!\r\n";

void uart_init (void)
{
	uint8_t dummy;
	
	UBRR3 = 8;
	// UCSR3B = (1 << RXEN3)|(1 << TXEN3)|(1 << RXCIE3);
	UCSR3B = (1 << RXEN3)|(1 << TXEN3);
	UCSR3C = (1 << UCSZ31)|(1 << UCSZ30);
	
	// flush receiver buffer;
	while ( UCSR3A & (1<<RXC3) ) dummy = UDR3;
	
	UBRR2 = 8;
	UCSR2B = (1 << RXEN2)|(1 << TXEN2)|(1 << RXCIE2);
	UCSR2C = (1 << UCSZ21)|(1 << UCSZ20);
	
	// flush receiver buffer;
	while ( UCSR2A & (1<<RXC2) ) dummy = UDR2;
}

void uart_sendC (const uint8_t data)
{
	while (!(UCSR3A & (1 << UDRE3)));
	UDR3 = data;
}

uint8_t uart_getData (void)
{
	if (UCSR3A & (1<<RXC3)) 
	{
		return UDR3;
	}
	else 
	{
		return 0;
	}
}


bool uart_hasData (void)
{
	if (UCSR3A & (1<<RXC3))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void uart2_sendC (const uint8_t data)
{
	while (!(UCSR2A & (1 << UDRE2)));
	UDR2 = data;
}

void uart_sendS(const uint8_t *pData, uint16_t size)
{
	uint16_t cnt = 0;
	
	while (cnt < size)
	{
		uart_sendC(pData[cnt]);
		cnt++;
	}
}

void uart2_sendS(const uint8_t *pData, uint16_t size)
{
	uint16_t cnt = 0;
	
	while (cnt < size)
	{
		uart2_sendC(pData[cnt]);
		cnt++;
	}
}

ISR(USART2_RX_vect)
{
	uint8_t data;
	
	data = UDR2;
	
	switch (data)
	{
		case 'A':
		PORTB ^= (1 << PB7);	// pb7 ist high
		break;
		case 'F':
		uart2_sendS((uint8_t*) string, sizeof(string)-1);
		break;
	}
	
}