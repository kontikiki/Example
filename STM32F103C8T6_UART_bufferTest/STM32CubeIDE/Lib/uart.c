/*
 * uart.c
 *
 *  Created on: 2023. 3. 27.
 *      Author: user
 */
#include "uart.h"


void rxBufferInit(ring_buffer_t *uart) {
	uart->head = 0;
	uart->tail = 0;
	memset(uart->buffer, 0, sizeof(RX_BUFFER_SIZE));
}

void push(ring_buffer_t *uart, uint8_t ch) {
	uint16_t i = (unsigned int) (uart->head + 1) % RX_BUFFER_SIZE;
	if (i != uart->tail) {
		uart->buffer[uart->head] = ch;
		uart->head = i;
	}
}

uint8_t pop(ring_buffer_t *uart) {

	if (uart->head == uart->tail) {
		return -1;
	} else {

		unsigned char cpop = uart->buffer[uart->tail];
		uart->tail = (uint16_t) (uart->tail + 1) % RX_BUFFER_SIZE;

		return cpop;

	}
}

int8_t uart_available(ring_buffer_t *uart) {

	uint8_t n = (unsigned int) (RX_BUFFER_SIZE + (uart->head) - (uart->tail))
			% RX_BUFFER_SIZE;
	return n;
}

