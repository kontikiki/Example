/*
 * Pixy2SPI.c
 *
 *  Created on: 2023. 2. 19.
 *      Author: user
 */
#include "Pixy2SPI.h"

SPI_HandleTypeDef* Pixy2_SPI;
GPIO_TypeDef* Pixy2_CS_Port;
uint16_t Pixy2_CS_Pin;

int8_t open(SPI_HandleTypeDef* hspi,GPIO_TypeDef* port,uint16_t cs_pin) {
		Pixy2_CS_Pin = cs_pin; // default slave select pin
	Pixy2_CS_Port=port;
	Pixy2_SPI=hspi;

	return 0;
}

void close() {
}

int16_t recv(uint8_t *buf, uint8_t len, uint16_t *cs) {
	uint8_t i;
	if (cs)
		*cs = 0;
	HAL_GPIO_WritePin(Pixy2_CS_Port, Pixy2_CS_Pin, GPIO_PIN_RESET);



	for (i = 0; i < len; i++) {
		uint8_t data;
		HAL_SPI_Receive(Pixy2_SPI, &data, 1, 5000);
		buf[i] = data;
		if (cs)
			*cs += buf[i];
	}

	HAL_GPIO_WritePin(Pixy2_CS_Port, Pixy2_CS_Pin, GPIO_PIN_SET);
	return len;
}

int16_t send(uint8_t *buf, uint8_t len) {

	HAL_GPIO_WritePin(Pixy2_CS_Port, Pixy2_CS_Pin, GPIO_PIN_RESET);


	for (int i = 0; i < len; i++) {
		HAL_SPI_Transmit(Pixy2_SPI, (uint8_t*) &buf[i], 1, 5000);
	}


	HAL_GPIO_WritePin(Pixy2_CS_Port, Pixy2_CS_Pin, GPIO_PIN_SET);

	return len;
}
