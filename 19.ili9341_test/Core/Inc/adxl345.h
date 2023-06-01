/*
 * adxl345.h
 *
 *  Created on: 2023. 1. 30.
 *      Author: user
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include "stm32f1xx_hal.h"
#include "stdio.h"


#define POWER_CTL      0x2D
#define DATA_FORMAT    0x31
#define BW_RATE        0x2C
#define DATAX0         0x32
#define DATAX1         0x33
#define DATAY0         0x34
#define DATAY1         0x35
#define DATAZ0         0x36
#define DATAZ1         0x37
#define FIFO_CTL       0x38
#define SPEED          0x0F          // Buffer Speed - 3200Hz

#define ACCEL_ERROR    0x02

//#define ACCEL_ADDRESS  0x1D          // if ALT ADDRESS = 1
#define ACCEL_ADDRESS  0x53          // if ALT ADDRESS = 0



void singleByteWrite(uint16_t address,uint16_t  data1);
void multiDataRead(int16_t *data_X, int16_t *data_Y, int16_t *data_Z);
uint16_t singleByteRead(uint16_t address);

int8_t ADXL345Init();
void accelAverage();

#endif /* ADXL345_H_ */
