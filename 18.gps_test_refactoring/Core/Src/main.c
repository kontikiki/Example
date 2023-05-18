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
#include "uart.h"
#include "u8g2.h"
#include "math.h"
#define pi 3.14159265358979323846

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define OLED
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
extern ring_buffer_t uart_rx;

int btnFlag = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int __io_putchar(int ch) {
	(void) HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 100);
	return ch;
}

double deg2rad(double deg) {
	return (deg * pi / 180);
}

double rad2deg(double rad) {
	return (rad * 180 / pi);
}

double calc_distance(double lat1, double lon1, double lat2, double lon2) {

	double radius = 6371.0;

	if ((lat1 == lat2) && (lon1 == lon2)) {
		return 0;
	} else {

		double dLat = deg2rad((lat2 - lat1)) / 2.0;
		double dLon = deg2rad((lon2 - lon1)) / 2.0;

		lat1 = deg2rad(lat1);
		lat2 = deg2rad(lat2);

		double a = sin(dLat) * sin(dLat)
				+ sin(dLon) * sin(dLon) * cos(lat1) * cos(lat2);
		double c = 2 * atan2f(sqrtf(a), sqrtf(1 - a));
		double dDistance = radius * c;

		dDistance *= 1000.0;

		return dDistance;
	}
	/*
	 double theta, dist;
	 if ((lat1 == lat2) && (lon1 == lon2)) {
	 return 0;
	 } else {
	 theta = lon1 - lon2;
	 dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2))
	 + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
	 dist = acos(dist);
	 dist = rad2deg(dist);
	 dist = dist * 60 * 1.1515;

	 dist = dist * 1.609344;
	 return (dist);
	 }
	 */

}

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
	static double f_latitude1 = 0.0;
	static double f_longitude1 = 0.0;
	double f_latitude2 = 0.0;
	double f_longitude2 = 0.0;

	double distance = 0.0;
	static double pre_time = 0.0;
	double f_seconds = 0.0;
	double time_interval = 0.0;
	double speed = 0.0;
	double ground_speed = 0.0;

	char str_buff[32];
	char str_buff2[32];
	char str_buff3[32];
	char str_buff4[32];

	char buff[1024];
	char type[16];
	char time[16];
	char valid[4];
	char latitude[16];
	char NS[4];
	char longitude[16];
	char EW[4];
	char groundSpeed[16];
	//char str8[18];
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
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_SPI1_Init();

	/* Initialize interrupts */
	MX_NVIC_Init();
	/* USER CODE BEGIN 2 */
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_spi,
			u8x8_stm32_gpio_and_delay);

	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);

	//u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);
	u8g2_SetFont(&u8g2, u8g2_font_6x13_mr);

	u8g2_SetDisplayRotation(&u8g2, U8G2_R2);

	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_ERR);
	/* Enable the UART Data Register not empty Interrupt */
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	rxBufferInit(&uart_rx);

	printf("this is MAIN code, not WHILE\r\n");

	sprintf(str_buff, "Hello :)");
	sprintf(str_buff2, "Push the button,");
	sprintf(str_buff3, "See your speed.");
	u8g2_FirstPage(&u8g2);
	do {

		u8g2_DrawStr(&u8g2, 2, 15, str_buff);
		u8g2_DrawStr(&u8g2, 2, 30, str_buff2);
		u8g2_DrawStr(&u8g2, 2, 45, str_buff3);

	} while (u8g2_NextPage(&u8g2));

	memset(str_buff, 0, sizeof(str_buff));
	memset(str_buff, 0, sizeof(str_buff2));
	memset(str_buff, 0, sizeof(str_buff3));

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1) {

		sprintf(str_buff, "Speed: %.3f km/h", speed);
		sprintf(str_buff2, "Distance: %.3f m", distance);
		sprintf(str_buff3, "Time interval: %.2f s", time_interval);
		sprintf(str_buff4, "Gnd Speed: %.3f km/h", ground_speed);
	//	sprintf(str_buff, "Latitude: %.6f", f_latitude2);
	//	sprintf(str_buff3, "Longitude: %.6f", f_longitude2);


		u8g2_FirstPage(&u8g2);
		do {

			u8g2_DrawStr(&u8g2, 2, 15, str_buff);
			u8g2_DrawStr(&u8g2, 2, 30, str_buff2);
			u8g2_DrawStr(&u8g2, 2, 45, str_buff3);
			u8g2_DrawStr(&u8g2, 2, 60, str_buff4);

		} while (u8g2_NextPage(&u8g2));

		memset(str_buff, 0, sizeof(str_buff));
		memset(str_buff, 0, sizeof(str_buff2));
		memset(str_buff, 0, sizeof(str_buff3));
		memset(str_buff, 0, sizeof(str_buff4));


		int i = 0;
		uint32_t tick = HAL_GetTick();
		while ((HAL_GetTick() - tick) < 1000) {
			if (uart_available(&uart_rx)) {
				int ch = pop(&uart_rx);
				if (ch != -1) {
					buff[i++] = ch;
				}
			}
		}
#ifndef OLED
	HAL_UART_Transmit(&huart1, (uint8_t*) buff, strlen(buff), 500);
#endif

		int k = 0;
		char *ptr;
		ptr = buff;

		while (((*ptr) != 'R') && (k < strlen(buff))) {
			k++;
			ptr++;
		}

		if ((*ptr) == 'R') {

			if ((*(ptr + 1)) == 'M' && (*(ptr + 2)) == 'C') {

				char *ptr2 = type;
				int n2 = 0;
				while ((*ptr) != ',') {
					memcpy(ptr2, ptr, 1);
					ptr2++;
					ptr++;
					n2++;
				}

				memcpy(ptr2, "\0", 1);

#ifndef OLED
			HAL_UART_Transmit(&huart1, (uint8_t*) type, n2 + 1, 500);

			HAL_UART_Transmit(&huart1, (uint8_t*) "\r", 1, 500);
			HAL_UART_Transmit(&huart1, (uint8_t*) "\n", 1, 500);
#endif
				ptr++;

				char *ptr3 = time;

				int n3 = 0;
				while ((*ptr) != ',') {
					memcpy(ptr3, ptr, 1);

					ptr3++;
					ptr++;
					n3++;
				}

				memcpy(ptr3, "\0", 1);

				if (n3 == 9) {
					char hour[5] = { 0, };
					char minute[5] = { 0, };
					char second[10] = { 0, };

					memcpy(hour, time, 2);
					memcpy(&hour[2], "\0", 1);

					memcpy(minute, &time[2], 2);
					memcpy(&minute[2], "\0", 1);

					memcpy(second, &time[4], 5);
					memcpy(&second[5], "\0", 1);

					f_seconds = (atof(hour) * 60.0 * 60.0)
							+ (atof(minute) * 60.0) + (atof(second));

#ifndef OLED
				printf("pre_time : %.2f\r\n", pre_time);

				printf("f_seconds : %.2f\r\n", f_seconds);
#endif

					if (pre_time == 0) {
						time_interval = 0.0;
					} else {
						time_interval = f_seconds - pre_time;
					}

#ifndef OLED
				printf("time_interval : %.2f\r\n", time_interval);
#endif

					pre_time = f_seconds;
				}

#ifndef OLED
			HAL_UART_Transmit(&huart1, (uint8_t*) time, n3 + 1, 500);

			HAL_UART_Transmit(&huart1, (uint8_t*) "\r", 1, 500);
			HAL_UART_Transmit(&huart1, (uint8_t*) "\n", 1, 500);
#endif

				ptr++;

				char *ptr4 = valid;

				int n4 = 0;
				while ((*ptr) != ',') {
					memcpy(ptr4, ptr, 1);
					ptr4++;
					ptr++;
					n4++;
				}

				memcpy(ptr4, "\0", 1);

#ifndef OLED
			HAL_UART_Transmit(&huart1, (uint8_t*) valid, n4 + 1, 500);

			printf("\r\n");
#endif

				ptr++;

				char *ptr5 = latitude;

				int n5 = 0;
				while ((*ptr) != ',') {
					memcpy(ptr5, ptr, 1);

					ptr5++;
					ptr++;
					n5++;
				}

				memcpy(ptr5, "\0", 1);

				if (n5 == 10) {
					double f_latitude = atof(latitude);
					if (f_latitude > 0) {
						int degree_latitude = ((int)f_latitude / 100);

						double minute_latitude = f_latitude
								- ((double)(degree_latitude) * 100.0);
						double minute2degree_latitude = minute_latitude
								/ 60.000;
						f_latitude2 = degree_latitude + minute2degree_latitude;
#ifndef OLED
					printf("latitude: %.7f\r\n", f_latitude2);
#endif
					}
				}

				//HAL_UART_Transmit(&huart1, (uint8_t*)latitude, n5+1, 500);

				ptr++;

				char *ptr6 = NS;

				int n6 = 0;
				while ((*ptr) != ',') {
					memcpy(ptr6, ptr, 1);
					ptr6++;
					ptr++;
					n6++;
				}

				memcpy(ptr6, "\0", 1);

#ifndef OLED
			HAL_UART_Transmit(&huart1, (uint8_t*) NS, n6 + 1, 500);

			printf("\r\n");
#endif

				ptr++;

				char *ptr7 = longitude;

				int n7 = 0;
				while ((*ptr) != ',') {
					memcpy(ptr7, ptr, 1);
					ptr7++;
					ptr++;
					n7++;
				}

				memcpy(ptr7, "\0", 1);

				if (n7 == 11) {
					double f_longitude = atof(longitude);
					if (f_longitude > 0) {
						int degree_longitude = ((int)f_longitude / 100);
						double minute_longitude = f_longitude
								- ((double)(degree_longitude) * 100.0);
						double minute2degree_longitude = minute_longitude
								/ 60.0;
						f_longitude2 = degree_longitude
								+ minute2degree_longitude;

#ifndef OLED
					printf("longitude: %.7f\r\n", f_longitude2);
#endif
					}
				}

				//HAL_UART_Transmit(&huart1, (uint8_t*)longitude, n7+1, 500);

				ptr++;

				char *ptr8 = EW;

				int n8 = 0;
				while ((*ptr) != ',') {
					memcpy(ptr8, ptr, 1);
					ptr8++;
					ptr++;
					n8++;
				}

				memcpy(ptr8, "\0", 1);

#ifndef OLED
			HAL_UART_Transmit(&huart1, (uint8_t*) EW, n8 + 1, 500);

			printf("\r\n");
#endif

				ptr++;

				char *ptr9 = groundSpeed;

				int n9 = 0;
				while ((*ptr) != ',') {
					memcpy(ptr9, ptr, 1);

					ptr9++;
					ptr++;
					n9++;
				}

				memcpy(ptr9, "\0", 1);

				if (n9 == 5) {
					ground_speed = (atof(groundSpeed)) * 1.852;
				}

#ifndef OLED
			HAL_UART_Transmit(&huart1, (uint8_t*) groundSpeed, n9 + 1, 500);

			printf("\r\n");
#endif

				if ((f_latitude1 == 0) && (f_longitude1 == 0)) {
					f_latitude1 = f_latitude2;
					f_longitude1 = f_longitude2;
				}

				if (time_interval >= 0.000 && f_latitude1 > 0) {

					distance = calc_distance(f_latitude1, f_longitude1,
							f_latitude2, f_longitude2);

#ifndef OLED
				printf("distance : %.7f\r\n", distance);
#endif

					f_latitude1 = f_latitude2;
					f_longitude1 = f_longitude2;
					if (distance == 0) {
						speed = 0.0;
					} else {
						speed = (distance * 0.001 * 3600.0) / time_interval;
					}

				}

#ifndef OLED
			printf("speed : %.7f\r\n", speed);
			printf("ground_speed : %.7f\r\n", ground_speed);
#endif

			}

			memset(type, 0, sizeof(type));
			memset(time, 0, sizeof(time));
			memset(latitude, 0, sizeof(latitude));
			memset(NS, 0, sizeof(NS));
			memset(longitude, 0, sizeof(longitude));
			memset(EW, 0, sizeof(EW));
			memset(groundSpeed, 0, sizeof(groundSpeed));

			memset(buff, 0, sizeof(buff));

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
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
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
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
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
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, OLED_RST_Pin | OLED_DC_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : btn0_Pin */
	GPIO_InitStruct.Pin = btn0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
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
/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == btn0_Pin) {
		if (btnFlag == 0) {
			btnFlag = 1;
		} else if (btnFlag == 1) {
			btnFlag = 0;
		}

	}
}
*/
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
