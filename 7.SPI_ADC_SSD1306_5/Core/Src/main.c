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
#include "stm32f4xx_hal.h"

#include "u8g2.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
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
ADC_HandleTypeDef hadc1;

SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */
const uint8_t sndBuff[]="VOLTAGE:";

float adcVal=0;
char buffer[5];
typedef struct _point
  {
	  int x;
	  int y;
  }Point;

int i=1;
Point point[128];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define bitmap_width 128
#define bitmap_height 64
static unsigned char bitmap[128*8]=
		{
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xf7, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xf7, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0x7f, 0xf7, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0x7f, 0xf7, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0xff, 0xff, 0xff,
						0xff, 0xff, 0x3f, 0xf7, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xbf, 0xff, 0xff, 0xef, 0xff, 0xff, 0xf7, 0xff, 0xfe, 0x3e, 0x3f, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xcf, 0xff, 0xff, 0xef, 0xff, 0xff, 0xe3, 0xff, 0xfe, 0x3e, 0x3f, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xe7, 0xff, 0xff, 0xef, 0xff, 0x8f, 0xe3, 0xff, 0xfe, 0x3e, 0x3f, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xf9, 0xff, 0xff, 0xdf, 0xff, 0x8f, 0xe3, 0xff, 0x7c, 0x3c, 0x3f, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xfe, 0xff, 0xff, 0xdf, 0xe7, 0x8f, 0xe3, 0xfc, 0x3c, 0x7c, 0x7f, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xcf, 0xc7, 0xe3, 0xf8, 0x3c, 0x7c, 0x7f, 0xdf, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0x9f, 0xc7, 0xe3, 0xf9, 0x3c, 0x7c, 0x7e, 0x0f, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0x07, 0xfe, 0x7f, 0x86, 0x03, 0xf1, 0x3c, 0x7c, 0x7c, 0x27, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0x07, 0xfe, 0xff, 0xc0, 0x03, 0xf3, 0x3c, 0x7c, 0x78, 0xe7, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xc7, 0xc3, 0xe2, 0x38, 0x78, 0x79, 0xe7, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xc7, 0xc3, 0xe0, 0x78, 0x78, 0x79, 0xe7, 0xff, 0xff,
						0xff, 0xe0, 0x7f, 0xfe, 0x03, 0xff, 0xff, 0xc7, 0xc3, 0x00, 0xf8, 0x78, 0x71, 0xe7, 0xff, 0xff,
						0xff, 0xff, 0x9f, 0xfc, 0x01, 0xff, 0xff, 0xc7, 0xc3, 0x03, 0xf8, 0x78, 0x71, 0xcf, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xff, 0xc7, 0xc3, 0xc7, 0xf0, 0x70, 0x71, 0x8f, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xff, 0xc7, 0xc3, 0xc7, 0xe0, 0x60, 0x71, 0x9f, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xf8, 0x00, 0xff, 0xff, 0xc7, 0xc7, 0xc3, 0xc0, 0x40, 0x71, 0x3f, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xf8, 0x20, 0xff, 0xff, 0xef, 0xc7, 0xe3, 0xe8, 0x68, 0x70, 0x3f, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xf8, 0x20, 0xff, 0xff, 0xff, 0xc7, 0xe1, 0xfc, 0x7c, 0x7c, 0xff, 0xff, 0xff,
						0xff, 0xff, 0x00, 0x00, 0x20, 0x00, 0x07, 0xff, 0xcf, 0xf0, 0x7e, 0xfe, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xfe, 0x00, 0x00, 0x70, 0x00, 0x03, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xcf, 0xfd, 0xff, 0xff,
						0xff, 0xfc, 0x00, 0x00, 0x70, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf9, 0xff, 0xff,
						0xff, 0xfc, 0x00, 0x00, 0x70, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xff,
						0xff, 0xfe, 0x00, 0x00, 0xf8, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xff,
						0xff, 0xff, 0x00, 0x7f, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xf9, 0xff, 0xff,
						0xff, 0xff, 0x80, 0x3f, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xf9, 0xff, 0xff,
						0xff, 0xff, 0xe0, 0x0f, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0x1f, 0xff, 0x1f, 0xf9, 0xff, 0xff,
						0xff, 0xff, 0xf0, 0x07, 0xff, 0x00, 0x7f, 0xfc, 0xff, 0xde, 0x0c, 0xff, 0x1f, 0xf9, 0xff, 0xff,
						0xff, 0xff, 0xfc, 0x03, 0xfe, 0x01, 0xff, 0xfc, 0xf3, 0x9c, 0xec, 0xe3, 0x1f, 0xf9, 0xff, 0xff,
						0xff, 0xff, 0xfe, 0x03, 0xfe, 0x03, 0xff, 0xfc, 0xe3, 0x9c, 0xec, 0xc7, 0x1f, 0x91, 0xff, 0xff,
						0xff, 0xff, 0xff, 0x03, 0xfe, 0x07, 0xff, 0xfc, 0x61, 0x99, 0xcc, 0x1f, 0x1f, 0x01, 0xff, 0xff,
						0xff, 0xff, 0xff, 0x07, 0xff, 0x07, 0xff, 0xfc, 0x61, 0xb9, 0xcc, 0x7f, 0x1e, 0x71, 0xff, 0xff,
						0xff, 0xff, 0xff, 0x07, 0x8f, 0x07, 0xff, 0xfc, 0x61, 0x39, 0x9c, 0x7e, 0x1c, 0xf1, 0xff, 0xff,
						0xff, 0xff, 0xfe, 0x06, 0x03, 0x03, 0xff, 0xfe, 0x49, 0x39, 0x3c, 0x7c, 0x1c, 0xf1, 0xff, 0xff,
						0xff, 0xff, 0x3e, 0x0c, 0x01, 0x83, 0xff, 0xfe, 0x58, 0x78, 0x3c, 0x79, 0x1c, 0xf1, 0xff, 0xff,
						0xff, 0xfe, 0x7e, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x18, 0x7c, 0x7e, 0x7f, 0x1c, 0x01, 0xff, 0xff,
						0xff, 0xfc, 0xfc, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x7c, 0x7f, 0xfe, 0xff, 0xbe, 0x03, 0xff, 0xff,
						0xff, 0xfb, 0xfc, 0x00, 0x20, 0x01, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xf3, 0xfc, 0x00, 0x70, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xe7, 0xf8, 0x01, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xcf, 0xf8, 0x03, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xf8, 0x0f, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xf8, 0x3f, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xfc, 0x7f, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		};
extern uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

static u8g2_t u8g2;

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
  MX_ADC1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */

  u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_spi, u8x8_stm32_gpio_and_delay);

  u8g2_InitDisplay(&u8g2);
  u8g2_SetPowerSave(&u8g2, 0);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  point[0].x=0;
  point[0].y=127;

  while (1)
  {


	  u8g2_FirstPage(&u8g2);


	  point[0].x=0;
	  point[0].y=point[127].y;

	  do
	  {


		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1,HAL_MAX_DELAY);
		  adcVal = HAL_ADC_GetValue(&hadc1);

		  int pixel_y=(int)adcVal*64/4096;
		  point[i].x=i;
		  point[i].y=64-pixel_y;

		  float voltage_y=adcVal*(3.3)/4096.0;

		  int char_y=100.0*voltage_y;

		  int hundred_y=char_y/100;
		  int ten_y=char_y/10-(hundred_y*10);
		  int one_y=char_y-hundred_y*100-ten_y*10;

		  buffer[0]='0'+hundred_y;
		  buffer[1]='.';
		  buffer[2]='0'+ten_y;
		  buffer[3]='0'+one_y;

	  	  u8g2_SetFont(&u8g2,u8g2_font_5x7_tr);
	  	  u8g2_DrawStrX2(&u8g2,0,15,buffer);

	  	  for(int j=0;j<i;j++)
	  	  {
	  	  	u8g2_DrawLine(&u8g2,point[j].x,point[j].y,point[j+1].x,point[j+1].y);
	  	  }

	  	  i++;
	  		//HAL_Delay(50);
	  	  if(i==128)
	  	  {
	  		  i=0;
	  		  break;
	  	  }


 }while (u8g2_NextPage(&u8g2));
	  //}while(1);


/*

	  u8g2_FirstPage(&u8g2);
	  	  	while(1)
	  	  		{
	  	  			//u8g2_ClearBuffer(&u8g2);
	  	  			//u8g2_SetDrawColor(&u8g2,1);
	  	  			//u8g2_SetBitmapMode(&u8g2,1);
	  	  			u8g2_DrawBitmap(&u8g2, 0, 0, 16, bitmap_height,  bitmap);

	  	  			//u8g2_SetFont(&u8g2,u8g2_font_5x7_tr);
	  	  			//u8g2_DrawStrX2(&u8g2,0,30,sndBuff);
	  	  			//u8g2_DrawStrX2(&u8g2,0,60,buffer);

	  	  		} while (u8g2_NextPage(&u8g2));
	  	  		//}
*/
	  /* USER CODE END WHILE */

	     /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = ENABLE;
  hadc1.Init.NbrOfDiscConversion = 1;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

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
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, OLED_RST_Pin|OLED_DC_Pin|OLED_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : OLED_RST_Pin OLED_DC_Pin OLED_CS_Pin */
  GPIO_InitStruct.Pin = OLED_RST_Pin|OLED_DC_Pin|OLED_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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
  while (1)
  {
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
