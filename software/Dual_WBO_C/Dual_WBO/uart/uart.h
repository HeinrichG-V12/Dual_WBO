/*
 * uart.h
 *
 * Created: 03.05.2022 11:34:42
 *  Author: Heinrich
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define UBRR_115k	8
#define UBRR_250k	3

#define UART_RX_BUFFER_SIZE		128
#define UART_RX_BUFFER_MASK		( UART_RX_BUFFER_SIZE - 1 )
#define UART_TX_BUFFER_SIZE		128
#define UART_TX_BUFFER_MASK		( UART_TX_BUFFER_SIZE - 1 )


void uart_init (void);
void uart_sendC (uint8_t data);
void uart_sendString (uint8_t *data, uint8_t length);


#endif /* UART_H_ */