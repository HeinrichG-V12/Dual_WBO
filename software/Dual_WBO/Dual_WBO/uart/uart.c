/*
 * uart.c
 *
 * Created: 03.05.2022 11:34:23
 *  Author: Heinrich
 */ 

#include "uart.h"

uint8_t UART_RX_BUFFER[UART_RX_BUFFER_SIZE];
static volatile uint8_t UART_rxHead;
static volatile uint8_t UART_rxTail;

uint8_t UART_TX_BUFFER[UART_TX_BUFFER_SIZE];
static volatile uint8_t UART_txHead;
static volatile uint8_t UART_txTail;

void uart_init (void)
{
	//init uart 1 with 115200, 8n1
	
	UBRR1 = UBRR_115k;
	
	UCSR1B |= (1 << RXCIE1)|(1 << RXEN1)|(1 << TXEN1);
	UCSR1C |= (1 << UCSZ11)|(1 << UCSZ10);
	UART_rxHead = 0;
	UART_rxTail = 0;
	UART_txHead = 0;
	UART_txTail = 0;
	
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
	uint8_t data, tmphead;
	
	data = UDR1; /* read the received data */
	/* calculate buffer index */
	tmphead = ( UART_rxHead + 1 ) & UART_RX_BUFFER_MASK;
	UART_rxHead = tmphead; /* store new index */
	if ( tmphead == UART_rxTail )
	{
		/* ERROR! Receive buffer overflow */
	}

	UART_RX_BUFFER[tmphead] = data; /* store received data in buffer */
}

