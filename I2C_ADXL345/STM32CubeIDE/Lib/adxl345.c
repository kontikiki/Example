/*
 * adxl345.c
 *
 *  Created on: 2023. 1. 30.
 *      Author: user
 */
#include "adxl345.h"

extern I2C_HandleTypeDef hi2c1;
uint8_t data[10];
extern float readings[3];

void singleByteWrite(uint16_t address,uint16_t  data1)
{
	data[0]=address;
	data[1]=data1;

	HAL_I2C_Master_Transmit(&hi2c1,ACCEL_ADDRESS<<1,data,2,100);
}


void multiDataRead(int16_t* data_X, int16_t* data_Y, int16_t* data_Z)
{
	data[0]=DATAX0;
	HAL_I2C_Master_Transmit(&hi2c1, ACCEL_ADDRESS<<1, data, 1, 50);
	HAL_I2C_Master_Receive(&hi2c1, ACCEL_ADDRESS<<1, data, 6, 50);

	*data_X =(data[0] | (data[1] << 8));
	*data_Y =(data[2] | (data[3] << 8));
	*data_Z =(data[4] | (data[5] << 8));
}


uint16_t singleByteRead(uint16_t address)
{
	data[0] = address;
	HAL_I2C_Master_Transmit(&hi2c1, ACCEL_ADDRESS<<1, data, 1, 50);
	HAL_I2C_Master_Receive(&hi2c1, ACCEL_ADDRESS<<1, data, 1, 50);
	return data[0];
}

int8_t ADXL345Init()
{
	char id = 0x00;
		// Go into standby mode to configure the device.
		singleByteWrite(0x2D, 0x00);
		id = singleByteRead(0x00);
		if (id != 0xE5)
		{
			printf("ERROR\n");
			return ACCEL_ERROR;
		}
		else
		{
			printf("ENABLE\n");
			singleByteWrite(DATA_FORMAT, 0x08);       // Full resolution, +/-2g, 4mg/LSB, right justified
			singleByteWrite(BW_RATE, 0x0A);           // Set 100 Hz data rate
			singleByteWrite(FIFO_CTL, 0x80);          // stream mode
			singleByteWrite(POWER_CTL, 0x08);         // POWER_CTL reg: measurement mode
			return 0x00;
		}
}

void accelAverage()
{
	int16_t i, sx, sy, sz, xx, yy, zz;

		// sum
		sx = sy = sz = 0;
		// average accelerometer reading over last 16 samples
		for (i=0; i<16; i++)
		{
			multiDataRead(&xx, &yy, &zz);
			sx += xx;
			sy += yy;
			sz += zz;
		}
		// average
		readings[0] = sx >> 4;
		readings[1] = sy >> 4;
		readings[2] = sz >> 4;
}
