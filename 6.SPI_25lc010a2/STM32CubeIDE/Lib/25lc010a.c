/*
 * 코드 출처 :
 * https://github.com/eziya
 *
 */

#include "25lc010a.h"

SPI_HandleTypeDef* EEPROM_SPI;
GPIO_TypeDef* EEPROM_SS_Port;
uint16_t EEPROM_SS_Pin;

static void SS_Select();
static void SS_Deselect();

void EEPROM_Init(SPI_HandleTypeDef* spi, GPIO_TypeDef* ss_port, uint16_t ss_pin)
{
	EEPROM_SPI = spi;
	EEPROM_SS_Port = ss_port;
	EEPROM_SS_Pin = ss_pin;
}

bool EEPROM_WriteEnable(void)
{
	uint8_t data = EEPROM_CMD_WREN;
	SS_Select();
	if(HAL_SPI_Transmit(EEPROM_SPI, &data, 1, HAL_MAX_DELAY) != HAL_OK) return false;
	SS_Deselect();

	return true;
}

bool EEPROM_ReadByte(uint8_t address, uint8_t* ret)
{
	uint8_t data[2] = {EEPROM_CMD_READ, address};

	SS_Select();
	if(HAL_SPI_Transmit(EEPROM_SPI, data, sizeof(data), HAL_MAX_DELAY) != HAL_OK) return false;
	if(HAL_SPI_Receive(EEPROM_SPI, ret, 1, HAL_MAX_DELAY) != HAL_OK) return false;
	SS_Deselect();

	return true;
}

bool EEPROM_ReadBuffer(uint8_t address, uint8_t *buffer, uint8_t length)
{
	for(uint8_t i=0; i < length; i++)
	{
		if(!EEPROM_ReadByte(address+i, &buffer[i])) return false;
	}

	return true;
}

bool EEPROM_WriteByte(uint8_t address, uint8_t data)
{
	uint8_t buffer[3] = {EEPROM_CMD_WRITE, address, data};

	if(!EEPROM_WriteEnable()) return false;
	SS_Select();
	if(HAL_SPI_Transmit(EEPROM_SPI, buffer, sizeof(buffer), HAL_MAX_DELAY) != HAL_OK) return false;
	SS_Deselect();

	/* Wait write cycle time 5ms */
	HAL_Delay(5);

	return true;
}

bool EEPROM_WriteBuffer(uint8_t address, uint8_t *buffer, uint8_t length)
{
	uint8_t data[2] = {EEPROM_CMD_WRITE, address};

	if(!EEPROM_WriteEnable()) return false;
	SS_Select();
	if(HAL_SPI_Transmit(EEPROM_SPI, data, sizeof(data), HAL_MAX_DELAY) != HAL_OK) return false;

	for(uint8_t i = 0; i < length; i++)
	{
		/* Handle Paging */
		if( (address+i) % EEPROM_PAGE_SIZE == 0 && i != 0 )
		{
			SS_Deselect();
			HAL_Delay(5);

			if(!EEPROM_WriteEnable()) return false;
			SS_Select();
			data[1] = address + i;
			if(HAL_SPI_Transmit(EEPROM_SPI, data, sizeof(data), HAL_MAX_DELAY) != HAL_OK) return false;
		}

		if(HAL_SPI_Transmit(EEPROM_SPI, &buffer[i], 1, HAL_MAX_DELAY) != HAL_OK) return false;
	}

	SS_Deselect();

	/* Wait write cycle time 5ms */
	HAL_Delay(5);

	return true;
}

bool EEPROM_EraseAll(void)
{
	uint8_t address = 0;
	uint8_t data[2] = {EEPROM_CMD_WRITE, address};

	if(!EEPROM_WriteEnable()) return false;

	while(address < EEPROM_TOTAL_SIZE)
	{
		SS_Select();
		if(HAL_SPI_Transmit(EEPROM_SPI, data, sizeof(data), HAL_MAX_DELAY) != HAL_OK) return false;

		for(uint8_t i=0; i < EEPROM_PAGE_SIZE; i++)
		{
			if(HAL_SPI_Transmit(EEPROM_SPI, &data[1], 1, HAL_MAX_DELAY) != HAL_OK) return false;
		}

		SS_Deselect();

		/* Wait write cycle time 5ms */
		HAL_Delay(5);
		address += EEPROM_PAGE_SIZE;
	}

	return true;
}

static void SS_Select()
{
	HAL_GPIO_WritePin(EEPROM_SS_Port, EEPROM_SS_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}

static void SS_Deselect()
{
	HAL_GPIO_WritePin(EEPROM_SS_Port, EEPROM_SS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
}
