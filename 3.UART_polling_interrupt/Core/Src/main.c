/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stdio.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/*
#define MAX_BUFFER_SIZE    (255)

typedef struct {
  uint8_t head;
  uint8_t tail;
  uint8_t buffer[MAX_BUFFER_SIZE];
}uart_t;

void push(uart_t*, uint8_t);
uint8_t pop(uart_t*);
uint8_t isEmpty(uart_t*);
*/
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
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

uint8_t RxBuffer[0xff];
volatile int i=0;
//#define DMA_BUF_SIZE 100
//uint8_t rx_dma_buf[DMA_BUF_SIZE];

int __io_putchar (int ch)
{
  (void)HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 100);
  return ch;
}
/*
#ifdef __cplusplus
extern "C" int _write(int32_t file, uint8_t *ptr, int32_t len) {
#else
int _write(int32_t file, uint8_t *ptr, int32_t len) {
#endif
    if( HAL_UART_Transmit(&huart1, ptr, len, len) == HAL_OK ) return len;
    else return 0;
}
*/


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//#define get_dma_data_length() huart1.hdmarx->Instance->NDTR
//#define get_dma_total_size()  huart1.RxXferSize

/*
void uart_rx_dma_handler(){
	//dma 버퍼에서 이미 가져온 데이터의 위치를 저장할 변수
	static uint32_t old_pos=0;
	//dma 버퍼에 현재 데이터가 채워진 위치를 저장할 변수
	uint32_t pos;

	//dma 버퍼에서 가져다 저장할 변수
	uint8_t rx_buf[DMA_BUF_SIZE];
	//uint32_t rx_size;

	//가져온 데이터를 출력하기 위한 변수들
	uint8_t ch;
	uint8_t i;

    //DMA 버퍼에서 가져온 데이터의 크기를 저장할 변수
	rx_size = 0;

	//dma 버퍼에 데이터가 채워진 위치 얻기
	pos = get_dma_total_size() - get_dma_data_length();

	//이전 위치와 현재 위치가 다르다면... (처리할 데이터가 있다)
	if(pos != old_pos) {
		//현재 위치가 이전에 저장한 위치보다 크다면 보통의 상황으로 이전 위치부터 현재위치까지 DMA 버퍼에서 데이터 가져옴.
		if(pos > old_pos) {
            //memcpy를 사용하려면 #include "string.h" 필요
			memcpy(rx_buf, &rx_dma_buf[old_pos], pos - old_pos);

			// DMA 버퍼에서 가져온 데이터 크기 저장
			rx_size += pos - old_pos;
		} else {
			//현재 위치가 이전 위치보다 아래에 존재한다면 DMA 버퍼가 한바퀴가 넘어간 상태(Overflow)
			//일단 이전에 가져온 위치부터 버퍼의 끝까지 모두 가져온다.
			memcpy(rx_buf, &rx_dma_buf[old_pos], get_dma_total_size() - old_pos);
			// 가져온 데이터 크기 저장.
			rx_size += get_dma_total_size() - old_pos;


			//끝까지 다 가져왔는데
            //현재 위치가 0보다 크다면 추가로 가져가야할 것이 있다는 얘기임
            //DMA 버퍼의 0번째부터 현재 위치까지 추가로 가져옴.
			if(pos > 0){
                //rx_buf 위치 주의!!
				memcpy(&rx_buf[get_dma_total_size() - old_pos], &rx_dma_buf[0], pos);
				// 추가로 가져온 데이터 크기 추가
				rx_size += pos;
			}
		}
		//현재 위치를 이전위치로 변경
		old_pos = pos;

		//가져온 데이터가 있다면
		if(rx_size > 0) {
			//크기 만큼 루프 출력!
			for(i = 0;i<rx_size;i++) {
				ch = rx_buf[i];
                // printf는 #include "stdio.h" 가 필요하고 기타적인 처리부분은 생략한다.
				printf("%c", ch);
                // 할 것! (to do?)
				//if(ch=='\n')
				//	printf("\n");
			}
			//printf("\n");
		}
	}
}
*/

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
  MX_USART1_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
 // init_uart(&uartBuffer);
  setbuf(stdout,NULL);
  //HAL_UART_Receive_DMA(&huart1, rx_dma_buf, DMA_BUF_SIZE);

  HAL_UART_Receive_IT(&huart1,RxBuffer+i,1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(RxBuffer[i]=='\n')
	  {
		  printf("%s",RxBuffer);
		  i=0;
	  }
	  else if(i>0xff)
	  {
		  i=0;
	  }

	  /*
	  if (isEmpty(&uartBuffer) == 0) {
	       data = pop(&uartBuffer);
	       HAL_UART_Transmit(&huart1,&data,1,5000);
	     }
*/
	  //uart_rx_dma_handler();

/*
	  if(HAL_UART_Receive(&huart1, (uint8_t*)RxBuffer,1, 5000)== HAL_OK)
	  		{

	  			HAL_UART_Transmit(&huart1, (uint8_t*)RxBuffer, 1, 5000);
	  		}
  */


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
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
  /* DMA2_Stream7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
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
  huart1.Init.BaudRate = 9600;
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
  __HAL_RCC_DMA2_CLK_ENABLE();

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}


/* USER CODE BEGIN 4 */


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if (huart->Instance == huart1.Instance) {
	//    push(&uartBuffer, rxData);
		i++;
	    HAL_UART_Receive_IT(&huart1, RxBuffer+i, 1);

	  }
	//HAL_UART_Transmit(&huart1,RxBuffer,10,5000);
}
/*

void init_uart(uart_t* u)
{
  u->head = 0;
  u->tail = 0;
  memset(u->buffer, 0, sizeof(u->buffer));
}

void push(uart_t* u, uint8_t data)
{
  u->buffer[u->head] = data;

  u->head++;

  if (u->head >= MAX_BUFFER_SIZE) {
    u->head = 0;
  }
}

uint8_t pop(uart_t* u)
{
  uint8_t data = u->buffer[u->tail];

  u->tail++;

  if (u->tail >= MAX_BUFFER_SIZE) {
    u->tail = 0;
  }

  return data;
}

uint8_t isEmpty(uart_t* u)
{
  return u->head == u->tail;
}
*/

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
