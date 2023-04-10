/*
 * uart.h
 *
 *  Created on: 2023. 3. 27.
 *      Author: user
 */

#ifndef LIB_UART_H_
#define LIB_UART_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stm32f1xx_hal.h"

#define RX_BUFFER_SIZE 32

typedef struct _ring_buffer {
	uint8_t buffer[RX_BUFFER_SIZE];
	volatile uint16_t head;
	volatile uint16_t tail;
} ring_buffer_t;

void push(ring_buffer_t*, uint8_t);
uint8_t pop(ring_buffer_t*);
void rxBufferInit(ring_buffer_t*);
int8_t uart_available(ring_buffer_t*);

#endif /* LIB_UART_H_ */
