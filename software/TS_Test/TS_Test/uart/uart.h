/*
 * uart.h
 *
 * Created: 03.05.2022 20:21:28
 *  Author: Heinrich
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

#define UART_RX_BUFFER_SIZE 16
#define UART_RX_COUNT		5
#define UART_TX_BUFFER_SIZE 32

void uart_init (void);
void uart_sendC (const uint8_t data);
uint8_t uart_getData (void);
bool uart_hasData (void);
void uart_sendS(const uint8_t *pData, uint16_t size);

void uart2_sendC (const uint8_t data);
void uart2_sendS(const uint8_t *pData, uint16_t size);

#endif /* UART_H_ */