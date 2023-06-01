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
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "adxl345.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
char buffer[10];

typedef struct _point {
	int x;
	int y;
} Point;

Point point[100];

float readings[3] = { 0, 0, 0 }; // X, Y and Z buffer
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch) {
	(void) HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 100);
	return ch;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

	ILI9341_Init();

	// Simple Text writing (Text, Font, X, Y, Color, BackColor)
	// Available Fonts are FONT1, FONT2, FONT3 and FONT4
	//ILI9341_FillScreen(WHITE);
	ILI9341_SetRotation(SCREEN_HORIZONTAL_1);
	//ILI9341_DrawText("HELLO WORLD", FONT4, 90, 110, BLACK, WHITE);
	//HAL_Delay(1000);

	//Writing numbers
	ILI9341_FillScreen(BLACK);
	/*
	 static char BufferText[30];
	 for (uint8_t i = 0; i <= 5; i++) {
	 sprintf(BufferText, "COUNT : %d", i);
	 ILI9341_DrawText(BufferText, FONT3, 10, 10, BLACK, WHITE);
	 ILI9341_DrawText(BufferText, FONT3, 10, 30, BLUE, WHITE);
	 ILI9341_DrawText(BufferText, FONT3, 10, 50, RED, WHITE);
	 ILI9341_DrawText(BufferText, FONT3, 10, 70, GREEN, WHITE);
	 ILI9341_DrawText(BufferText, FONT3, 10, 90, YELLOW, WHITE);
	 ILI9341_DrawText(BufferText, FONT3, 10, 110, PURPLE, WHITE);
	 ILI9341_DrawText(BufferText, FONT3, 10, 130, ORANGE, WHITE);
	 ILI9341_DrawText(BufferText, FONT3, 10, 150, MAROON, WHITE);
	 ILI9341_DrawText(BufferText, FONT3, 10, 170, WHITE, BLACK);
	 ILI9341_DrawText(BufferText, FONT3, 10, 190, BLUE, BLACK);
	 }

	 // Horizontal Line (X, Y, Length, Color)
	 ILI9341_FillScreen(WHITE);
	 ILI9341_DrawHLine(50, 120, 200, NAVY);
	 HAL_Delay(1000);

	 // Vertical Line (X, Y, Length, Color)
	 ILI9341_FillScreen(WHITE);
	 ILI9341_DrawVLine(160, 40, 150, DARKGREEN);
	 HAL_Delay(1000);

	 // Hollow Circle (Centre X, Centre Y, Radius, Color)
	 ILI9341_FillScreen(WHITE);
	 ILI9341_DrawHollowCircle(160, 120, 80, PINK);
	 HAL_Delay(1000);

	 // Filled Circle (Centre X, Centre Y, Radius, Color)
	 ILI9341_FillScreen(WHITE);
	 ILI9341_DrawFilledCircle(160, 120, 50, CYAN);
	 HAL_Delay(1000);

	 // Filled Rectangle (Start X, Start Y, Length X, Length Y)
	 ILI9341_FillScreen(WHITE);
	 ILI9341_DrawRectangle(50, 50, 220, 140, GREENYELLOW);
	 HAL_Delay(1000);

	 // Hollow Rectangle (Start X, Start Y, End X, End Y)
	 ILI9341_FillScreen(WHITE);
	 ILI9341_DrawHollowRectangleCoord(50, 50, 270, 190, DARKCYAN);
	 HAL_Delay(1000);

	 // Simple Pixel Only (X, Y, Color)
	 ILI9341_FillScreen(WHITE);
	 ILI9341_DrawPixel(100, 100, BLACK);
	 HAL_Delay(1000);
	 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	ADXL345Init();
	accelAverage();

	for (int i = 0; i < 25; i++) {
		int gap = rand() % 50;
		point[i].x = 160 - gap;
		point[i].y = 120 - gap;
	}

	for (int i = 25; i < 50; i++) {
		int gap = rand() % 50;
		point[i].x = 160 + gap;
		point[i].y = 120 + gap;
	}
	for (int i = 50; i < 75; i++) {
		int gap = rand() % 50;
		point[i].x = 160 + gap;
		point[i].y = 120 - gap;
	}
	for (int i = 75; i < 100; i++) {
		int gap = rand() % 50;
		point[i].x = 160 - gap;
		point[i].y = 120 + gap;
	}


	 int rad[100];
	 for (int i = 0; i < 100; i++) {
	 rad[i] = rand() % 20;
	 }


	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		// ILI9341_FillScreen(BLACK);
		int16_t x, y, z = 0;
		multiDataRead(&x, &y, &z);
		x -= readings[0];
		y -= readings[1];
		z -= readings[2];
		z += 256;
		printf("%d %d %d\r\n", x, y, z);

		for (int i = 0; i < 25; i++) {
			float ratio = rand() % 100;
			ratio = ratio * 0.01;
			int pixel_y = ratio * x * 120 / 512;
			int pixel_x = ratio * y * 160 / 512;
			ILI9341_DrawPixel(point[i].x, point[i].y, BLACK);

			//ILI9341_DrawHollowCircle(point[i].x, point[i].y, rad[i], BLACK);
			//ILI9341_DrawText("HELLO", FONT4, point[i].x, point[i].y, BLACK, BLACK);

			point[i].x = point[i].x - pixel_x;
			point[i].y = point[i].y - pixel_y;

			if (point[i].x > 319) {
				point[i].x = 319;
			} else if (point[i].x < 0) {
				point[i].x = 0;
			}

			if (point[i].y > 239) {
				point[i].y = 239;
			} else if (point[i].y < 0) {
				point[i].y = 0;
			}
			ILI9341_DrawPixel(point[i].x, point[i].y, GREEN);
			//ILI9341_DrawHollowCircle(point[i].x, point[i].y, rad[i], GREEN);
			//ILI9341_DrawText("HELLO", FONT4, point[i].x, point[i].y, WHITE, BLACK);
		}

		for (int i = 25; i < 50; i++) {
			float ratio = rand() % 100;
			ratio = ratio * 0.01;
			int pixel_y = ratio * x * 120 / 512;
			int pixel_x = ratio * y * 160 / 512;
			ILI9341_DrawPixel(point[i].x, point[i].y, BLACK);

			//ILI9341_DrawHollowCircle(point[i].x, point[i].y, rad[i], BLACK);
			//ILI9341_DrawText("WORLD", FONT4, point[i].x, point[i].y, BLACK, BLACK);

			point[i].x = point[i].x - pixel_x;
			point[i].y = point[i].y - pixel_y;

			if (point[i].x > 319) {
				point[i].x = 319;
			} else if (point[i].x < 0) {
				point[i].x = 0;
			}

			if (point[i].y > 239) {
				point[i].y = 239;
			} else if (point[i].y < 0) {
				point[i].y = 0;
			}
			ILI9341_DrawPixel(point[i].x, point[i].y, CYAN);
			//ILI9341_DrawHollowCircle(point[i].x, point[i].y, rad[i], CYAN);
			//ILI9341_DrawText("WORLD", FONT4, point[i].x, point[i].y, WHITE, BLACK);
		}

		for (int i = 50; i < 75; i++) {
			float ratio = rand() % 100;
			ratio = ratio * 0.01;
			int pixel_y = ratio * x * 120 / 512;
			int pixel_x = ratio * y * 160 / 512;
			ILI9341_DrawPixel(point[i].x, point[i].y, BLACK);

			//ILI9341_DrawHollowCircle(point[i].x, point[i].y, rad[i], BLACK);
			//ILI9341_DrawText("pill", FONT4, point[i].x, point[i].y, BLACK, BLACK);

			point[i].x = point[i].x - pixel_x;
			point[i].y = point[i].y - pixel_y;

			if (point[i].x > 319) {
				point[i].x = 319;
			} else if (point[i].x < 0) {
				point[i].x = 0;
			}

			if (point[i].y > 239) {
				point[i].y = 239;
			} else if (point[i].y < 0) {
				point[i].y = 0;
			}
			ILI9341_DrawPixel(point[i].x, point[i].y, YELLOW);
			//ILI9341_DrawHollowCircle(point[i].x, point[i].y, rad[i], YELLOW);
			//ILI9341_DrawText("pill", FONT4, point[i].x, point[i].y, WHITE, BLACK);
		}

		for (int i = 75; i < 100; i++) {
			float ratio = rand() % 100;
			ratio = ratio * 0.01;
			int pixel_y = ratio * x * 120 / 512;
			int pixel_x = ratio * y * 160 / 512;
			ILI9341_DrawPixel(point[i].x, point[i].y, BLACK);

			//ILI9341_DrawHollowCircle(point[i].x, point[i].y, rad[i], BLACK);
			//ILI9341_DrawText("blue", FONT4, point[i].x, point[i].y, BLACK, BLACK);

			point[i].x = point[i].x - pixel_x;
			point[i].y = point[i].y - pixel_y;

			if (point[i].x > 319) {
				point[i].x = 319;
			} else if (point[i].x < 0) {
				point[i].x = 0;
			}

			if (point[i].y > 239) {
				point[i].y = 239;
			} else if (point[i].y < 0) {
				point[i].y = 0;
			}
			ILI9341_DrawPixel(point[i].x, point[i].y, ORANGE);
			//ILI9341_DrawHollowCircle(point[i].x, point[i].y, rad[i], ORANGE);
			//ILI9341_DrawText("blue", FONT4, point[i].x, point[i].y, WHITE, BLACK);
		}

	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

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
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
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
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_RST_Pin|LCD_DC_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LCD_RST_Pin LCD_DC_Pin */
  GPIO_InitStruct.Pin = LCD_RST_Pin|LCD_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_CS_Pin */
  GPIO_InitStruct.Pin = LCD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LCD_CS_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
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
