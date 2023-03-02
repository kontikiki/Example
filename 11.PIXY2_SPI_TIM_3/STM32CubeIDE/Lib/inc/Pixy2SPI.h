/*
 * Pixy2SPI.h
 *
 *  Created on: 2023. 2. 19.
 *      Author: user
 */


#include "stm32f4xx_hal.h"

int8_t open(SPI_HandleTypeDef* hspi,GPIO_TypeDef* port,uint16_t cs_pin);
void close();
int16_t recv(uint8_t *buf, uint8_t len, uint16_t *cs);
int16_t send(uint8_t *buf, uint8_t len);
