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
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
uint8_t data;
uint8_t cmd;
uint8_t buff[20];
char str[32];
char str2[32];
char str3[50];

uint8_t timerFlag = 0;
uint8_t timerContinueFlag = 1;
uint8_t btnFlag = 0;
uint8_t btnContinueFlag = 1;

int state = 0;
int i = 0;

uint8_t getDataCommand[5] = { 0x11, 0x02, 0x0B, 0x01, 0xE1 };
uint8_t singleModeSetCommand[6] = { 0x11, 0x03, 0x0D, SAMPLING_TIME_HIGH,
SAMPLING_TIME_LOW, 0xBB };
uint8_t continuousModeSetCommand[6] = { 0x11, 0x03, 0x0D, 0xFF, 0xFF, 0xE1 };

uint8_t timingModeSetCommand[6] = { 0x11, 0x03, 0x05, DURATION_TIME_HIGH,
DURATION_TIME_LOW, 0xBA };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_SPI2_Init(void);
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
	MX_TIM2_Init();
	MX_USART1_UART_Init();
	MX_USART6_UART_Init();
	MX_SPI2_Init();

	/* Initialize interrupts */
	MX_NVIC_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);

	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_spi,
			u8x8_stm32_gpio_and_delay);

	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);

	u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		if (HAL_UART_Receive(&huart1, (uint8_t*) &cmd, 1, 5000) == HAL_OK) {
			data = cmd;
		}

		if (btnFlag == 1 && btnContinueFlag == 1) {
			if (i == 0) {
				data = '3';
				i++;
			} else if (i == 1) {
				data = '1';
				i++;
			} else if (i == 2) {
				data = '2';
				i = 0;
				btnFlag = 0;
			}
		}

		if (timerFlag == 1 && timerContinueFlag == 1) {
			if (i == 0) {
				data = '3';
				i++;
			} else if (i == 1) {
				data = '1';
				i++;
			} else if (i == 2) {
				data = '2';
				i = 0;
				timerFlag = 0;
			}
		}

		if (timerContinueFlag == 1 || btnContinueFlag == 1) {
			memset(buff, 0, 20);
			switch (data) {
			case '1':
				HAL_UART_Transmit(&huart6, (uint8_t*) getDataCommand, 5, 5000);
				if (HAL_UART_Receive(&huart6, (uint8_t*) buff, 20, 100)
						== HAL_OK) {
					state = 1;
				}
				break;

			case '2':
				HAL_UART_Transmit(&huart6, (uint8_t*) singleModeSetCommand, 6,
						5000);
				if (HAL_UART_Receive(&huart6, (uint8_t*) buff, 6, 100)
						== HAL_OK) {
					state = 2;
					timerContinueFlag = 0;

					btnContinueFlag = 0;
				}
				break;

			case '3':
				HAL_UART_Transmit(&huart6, (uint8_t*) continuousModeSetCommand,
						6, 5000);
				if (HAL_UART_Receive(&huart6, (uint8_t*) buff, 6, 100)
						== HAL_OK) {
					state = 2;

				}
				break;

			case '4':
				HAL_UART_Transmit(&huart6, (uint8_t*) timingModeSetCommand, 6,
						5000);
				if (HAL_UART_Receive(&huart6, (uint8_t*) buff, 6, 100)
						== HAL_OK) {
					state = 2;

				}
				break;

			default:
				break;
			}
		}

		if (state == 1) {
			//if (HAL_UART_Receive(&huart6, (uint8_t*) buff, 20, 100) == HAL_OK) {

			//HAL_UART_Transmit(&huart1, (uint8_t*) buff, 20, 100);

			if (buff[0] == 0x16 && buff[1] == 0x11) {
				if (buff[2] == 0x0B) {
					int val = 0;
					val |= (buff[3] << 24) | (buff[4] << 16) | (buff[5] << 8)
							| buff[6];
					sprintf(str, "PM2.5 : %d\r\n", val);
#ifndef OLED
							HAL_UART_Transmit(&huart1, (uint8_t*) str, sizeof(str),
									100);
		#endif
					val = 0;
					val |= (buff[7] << 24) | (buff[8] << 16) | (buff[9] << 8)
							| buff[10];
					sprintf(str2, "PM10 : %d\r\n", val);
#ifndef OLED
							HAL_UART_Transmit(&huart1, (uint8_t*) str2, sizeof(str2),
									5000);
		#else
					u8g2_FirstPage(&u8g2);
					do {
						u8g2_DrawStrX2(&u8g2, 17, 15, str);
						u8g2_DrawStrX2(&u8g2, 22, 30, str2);
					} while (u8g2_NextPage(&u8g2));
#endif

					memset(str, 0, sizeof(str));
					memset(str2, 0, sizeof(str2));
				}
			}

			//memset(buff, 0, 20);

		}

		else if (state == 2) {
			//	if (HAL_UART_Receive(&huart6, (uint8_t*) buff, 6, 100) == HAL_OK) {

			//HAL_UART_Transmit(&huart1, (uint8_t*) buff, 6, 100);

			if (buff[0] == 0x16 && buff[1] == 0x03) {
				if (buff[2] == 0x0D) {
					if (buff[3] == 0xff && buff[4] == 0xff) {
						sprintf(str3, "continuous mode\r\n");
#ifndef OLED
								HAL_UART_Transmit(&huart1, (uint8_t*) str3,
										sizeof(str3), 5000);
		#else
						u8g2_FirstPage(&u8g2);

						do {
							u8g2_DrawStr(&u8g2, 0, 30, str3);
						} while (u8g2_NextPage(&u8g2));
#endif
						memset(str3, 0, 50);
					} else {
						int measurement_time = (buff[3] << 8) | buff[4];
						/*sprintf(str3, "single mode time : %d sec\r\n",
								measurement_time);*/
						sprintf(str3,"stop state,interval 1 min\r\n");

#ifndef OLED
								HAL_UART_Transmit(&huart1, (uint8_t*) str3,
										sizeof(str3), 5000);
		#else
						u8g2_FirstPage(&u8g2);
						do {

							u8g2_DrawStr(&u8g2, 0, 30, str3);
						} while (u8g2_NextPage(&u8g2));
#endif
						memset(str3, 0, 50);
					}
				} else if (buff[2] == 0x05) {
					int duration_time = (buff[3] << 8) | buff[4];
					sprintf(str3, "timing mode interval : %d sec\r\n",
							duration_time);
#ifndef OLED
							HAL_UART_Transmit(&huart1, (uint8_t*) str3, sizeof(str3),
									5000);
		#else
					u8g2_FirstPage(&u8g2);
					do {

						u8g2_DrawStr(&u8g2, 0, 30, str3);
					} while (u8g2_NextPage(&u8g2));
#endif
					memset(str3, 0, 50);
				}
			}

			//memset(buff, 0, 20);

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

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 180;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Activate the Over-Drive mode
	 */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief NVIC Configuration.
 * @retval None
 */
static void MX_NVIC_Init(void) {
	/* TIM2_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	/* EXTI0_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/**
 * @brief SPI2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI2_Init(void) {

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI2_Init 2 */

	/* USER CODE END SPI2_Init 2 */

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
	htim2.Init.Prescaler = 9999;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 539999;
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
 * @brief USART6 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART6_UART_Init(void) {

	/* USER CODE BEGIN USART6_Init 0 */

	/* USER CODE END USART6_Init 0 */

	/* USER CODE BEGIN USART6_Init 1 */

	/* USER CODE END USART6_Init 1 */
	huart6.Instance = USART6;
	huart6.Init.BaudRate = 9600;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART6_Init 2 */

	/* USER CODE END USART6_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, OLED_RST_Pin | OLED_DC_Pin | OLED_CS_Pin,
			GPIO_PIN_SET);

	/*Configure GPIO pins : OLED_RST_Pin OLED_DC_Pin OLED_CS_Pin */
	GPIO_InitStruct.Pin = OLED_RST_Pin | OLED_DC_Pin | OLED_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : btn0_Pin */
	GPIO_InitStruct.Pin = btn0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(btn0_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	//GPIO PIN OUTPUT HIGH
	if (htim->Instance == htim2.Instance) {
		timerFlag = 1;
		timerContinueFlag = 1;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == btn0_Pin) {

			btnFlag = 1;
			btnContinueFlag = 1;

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
