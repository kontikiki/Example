/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "u8g2.h"
#include "uart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SAMPLING_TIME_HIGH 0x00
#define SAMPLING_TIME_LOW 0x24
#define DURATION_TIME_HIGH 0x01
#define DURATION_TIME_LOW 0x2C
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define OLED
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

extern ring_buffer_t uart_rx;

uint8_t buff[55];

uint8_t data;
uint8_t cmd;

uint8_t getDataCommand[5] = { 0x11, 0x02, 0x0B, 0x07, 0xDB };
uint8_t closeCommand[6] = { 0x11, 0x03, 0x0C, 0x01,
0x1E, 0xC1 };
uint8_t openCommand[6] = { 0x11, 0x03, 0x0C, 0x02, 0x1E, 0xC0 };

uint8_t timingModeSetCommand[6] = { 0x11, 0x03, 0x05, DURATION_TIME_HIGH,
DURATION_TIME_LOW, 0xBA };

volatile uint8_t btnFlag = 0;
volatile uint8_t timerFlag = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg,
		uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg,
		uint8_t arg_int, void *arg_ptr);

static u8g2_t u8g2;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	char str[32];
	char str2[32];
	char str3[32];
	int state = 0;
	int pre_tick = 0;
	int first = 0;
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI1_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_TIM2_Init();

	/* Initialize interrupts */
	MX_NVIC_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_spi,
			u8x8_stm32_gpio_and_delay);

	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);

	u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);

	//HAL_UART_Receive_IT(&huart1, &cmd, 1);

	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_ERR);
	/* Enable the UART Data Register not empty Interrupt */
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	rxBufferInit(&uart_rx);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		if (timerFlag == 1) {
			timerFlag = 0;

			state = 2;

			if (first++ > 0) {
				sprintf(str, "1 min TIMER");
				first = 1;

			} else {
				sprintf(str, "Hello :)");
			}

			u8g2_FirstPage(&u8g2);
			do {
				u8g2_DrawStrX2(&u8g2, 5, 30, str);

			} while (u8g2_NextPage(&u8g2));

		}

		if (btnFlag == 1) {
			btnFlag = 0;

			state = 2;
			sprintf(str, "BUTTON!");
			u8g2_FirstPage(&u8g2);
			do {
				u8g2_DrawStrX2(&u8g2, 5, 30, str);

			} while (u8g2_NextPage(&u8g2));

		}

		if (state == 1) {
			state = 3;
			sprintf(str, "MEASURING..");
						u8g2_FirstPage(&u8g2);
						do {
							u8g2_DrawStrX2(&u8g2, 5, 30, str);

						} while (u8g2_NextPage(&u8g2));
			pre_tick = HAL_GetTick();
			while ((HAL_GetTick() - pre_tick) < 5000)
				;

			memset(buff, 0, 55);
			HAL_UART_Transmit(&huart2, (uint8_t*) getDataCommand, 5, 5000);

			pre_tick = HAL_GetTick();
			while ((HAL_GetTick() - pre_tick) < 1000)
				;

			uint8_t num = uart_available(&uart_rx);
			uint8_t i;
			for (i = 0; i < num; i++) {
				int ch = pop(&uart_rx);
				if (ch != -1) {

					buff[i] = ch;
				}
			}
			//HAL_UART_Transmit(&huart1, buff, num, 500);

			if ((buff[0] == 0x16 && buff[1] == 0x35)) {
				if (buff[2] == 0x0B) {
					int val = 0;
					val |= (buff[3] << 24) | (buff[4] << 16) | (buff[5] << 8)
							| buff[6];
					sprintf(str, "PM1.0 : %d\r\n", val);
#ifndef OLED
	  					HAL_UART_Transmit(&huart1, (uint8_t*) str, sizeof(str),
	  							100);
	  #endif
					val = 0;
					val |= (buff[7] << 24) | (buff[8] << 16) | (buff[9] << 8)
							| buff[10];
					sprintf(str2, "PM2.5 : %d\r\n", val);
#ifndef OLED
	  					HAL_UART_Transmit(&huart1, (uint8_t*) str2, sizeof(str2),
	  							5000);
	  #endif
					val = 0;
					val |= (buff[11] << 24) | (buff[12] << 16) | (buff[13] << 8)
							| buff[14];
					sprintf(str3, "PM10 : %d\r\n", val);

#ifndef OLED
	  					HAL_UART_Transmit(&huart1, (uint8_t*) str3, sizeof(str3),
	  												5000);
	  #else
					u8g2_FirstPage(&u8g2);
					do {
						u8g2_DrawStrX2(&u8g2, 5, 15, str);
						u8g2_DrawStrX2(&u8g2, 5, 30, str2);
						u8g2_DrawStrX2(&u8g2, 5, 45, str3);
					} while (u8g2_NextPage(&u8g2));
					int pre_tick = HAL_GetTick();
					while ((HAL_GetTick() - pre_tick) < 1000)
						;

#endif

					memset(str, 0, sizeof(str));
					memset(str2, 0, sizeof(str2));
				}

			}
		}

		else if (state == 2) {
			state = 1;

			memset(buff, 0, 55);
			HAL_UART_Transmit(&huart2, (uint8_t*) openCommand, 6,
					5000);
			pre_tick = HAL_GetTick();
			while ((HAL_GetTick() - pre_tick) < 1000)
				;

			uint8_t num = uart_available(&uart_rx);

			uint8_t i;

			for (i = 0; i < num; i++) {
				int ch = pop(&uart_rx);
				if (ch != -1) {
					buff[i] = ch;
				}
			}
			//HAL_UART_Transmit(&huart1, buff, num, 500);

		} else if (state == 3) {
			state = 0;

			memset(buff, 0, 55);
			HAL_UART_Transmit(&huart2, (uint8_t*) closeCommand, 6,
					5000);
			pre_tick = HAL_GetTick();
			while ((HAL_GetTick() - pre_tick) < 1000)
				;

			uint8_t num = uart_available(&uart_rx);
			uint8_t i;

			for (i = 0; i < num; i++) {
				int ch = pop(&uart_rx);
				if (ch != -1) {
					buff[i] = ch;
				}
			}
			//HAL_UART_Transmit(&huart1, buff, num, 500);
		} else if (state == 0) {
			sprintf(str, "   ^   ^");
			sprintf(str2, "     o");
			u8g2_FirstPage(&u8g2);
			do {
				u8g2_DrawStrX2(&u8g2, 5, 30, str);
				u8g2_DrawStrX2(&u8g2, 5, 45, str2);

			} while (u8g2_NextPage(&u8g2));

			pre_tick = HAL_GetTick();
			while ((HAL_GetTick() - pre_tick) < 1000)
				;

			sprintf(str, "   -   -");
			sprintf(str2, "     _");
			u8g2_FirstPage(&u8g2);
			do {
				u8g2_DrawStrX2(&u8g2, 5, 30, str);
				u8g2_DrawStrX2(&u8g2, 5, 45, str2);

			} while (u8g2_NextPage(&u8g2));

			pre_tick = HAL_GetTick();
			while ((HAL_GetTick() - pre_tick) < 1000)
				;
		}

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief NVIC Configuration.
 * @retval None
 */
static void MX_NVIC_Init(void) {
	/* USART2_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	/* EXTI0_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	/* TIM2_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void) {

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 47999;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 9999;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, OLED_RST_Pin | OLED_DC_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : btn0_Pin */
	GPIO_InitStruct.Pin = btn0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(btn0_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : OLED_RST_Pin OLED_DC_Pin */
	GPIO_InitStruct.Pin = OLED_RST_Pin | OLED_DC_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : OLED_CS_Pin */
	GPIO_InitStruct.Pin = OLED_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(OLED_CS_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//GPIO PIN OUTPUT HIGH
	if (htim->Instance == htim2.Instance) {
		timerFlag = 1;

	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == btn0_Pin) {

		btnFlag = 1;

	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
