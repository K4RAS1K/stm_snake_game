/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "st7735.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ReadKey1 HAL_GPIO_ReadPin(GPIOA, move_up_Pin)
#define ReadKey2 HAL_GPIO_ReadPin(GPIOA, move_right_Pin)
#define ReadKey3 HAL_GPIO_ReadPin(GPIOA, move_down_Pin)
#define ReadKey4 HAL_GPIO_ReadPin(GPIOA, move_left_Pin)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern unsigned short testImage[];

bool flag_move_right = false;
bool flag_move_left = false;
bool flag_move_down = false;
bool flag_move_up = false;

int8_t move_num_x0 = 5;
int8_t move_num_x1 = 5;
int8_t move_num_y0 = 0;
int8_t move_num_y1 = 0;

typedef struct {
	uint8_t x0;
	uint8_t y0;
	uint8_t x1;
	uint8_t y1;
} Snake;

uint8_t playground[4] = { 7, 7, 126, 126 }; //to_change

void game_over(Snake head) {
	if (head.x1 < playground[0] || head.x1 > playground[2]) {
		ST7735_DrawRect(0, 0, 140, 140, ST7735_COLOR_RED);
		ST7735_DrawRect(20, 20, 60, 120, ST7735_COLOR_BLACK);
		ST7735_DrawRect(30, 30, 50, 110, ST7735_COLOR_RED);
		ST7735_DrawRect(30, 30, 60, 50, ST7735_COLOR_RED);

		ST7735_DrawRect(70, 20, 120, 120, ST7735_COLOR_BLACK);
		ST7735_DrawRect(80, 30, 110, 110, ST7735_COLOR_RED);
		while (1) {
			ST7735_DrawRect(30, 30, 50, 50, ST7735_COLOR_RED);
		}
	} else if (head.y1 < playground[1] || head.y1 > playground[3]) {
		ST7735_DrawRect(0, 0, 140, 140, ST7735_COLOR_RED);
		ST7735_DrawRect(20, 20, 60, 120, ST7735_COLOR_BLACK);
		ST7735_DrawRect(30, 30, 50, 110, ST7735_COLOR_RED);
		ST7735_DrawRect(30, 30, 60, 50, ST7735_COLOR_RED);

		ST7735_DrawRect(70, 20, 120, 120, ST7735_COLOR_BLACK);
		ST7735_DrawRect(80, 30, 110, 110, ST7735_COLOR_RED);
		while (1) {
			ST7735_DrawRect(30, 30, 50, 50, ST7735_COLOR_RED);

		}
	}
}

Snake* initialize_body() {
	uint8_t size = 2;
	Snake *body = malloc(size * sizeof(Snake));
	for (uint8_t i = 0; i < size; i++) {
		body[i].x0 = 5 + i;
		body[i].y0 = 5 + i;
		body[i].x1 = 5 + i;
		body[i].y1 = 5 + i;
	}
	return body;
}

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
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */
	ST7735_Init();

	ST7735_DrawRect(0, 0, 140, 140, ST7735_COLOR_BLACK);
	ST7735_DrawRect(playground[0], playground[1], playground[2], playground[3],
			ST7735_COLOR_WHITE);

	Snake head;

	head.x0 = 72;
	head.y0 = 72;
	head.x1 = 76;
	head.y1 = 76;

	Snake *body = initialize_body();

	Snake after_tail;

	after_tail.x0 = 15;
	after_tail.y0 = 15;
	after_tail.x1 = 15;
	after_tail.y1 = 15;

	srand(10);

	uint16_t body_size = 2;

	uint8_t move_num = 0;

	uint8_t delay_num = 0;
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		if (ReadKey1 == 1) {
			move_num = 3; // move_up
		}
		if (ReadKey2 == 1) {
			move_num = 0; // move_right
		}
		if (ReadKey3 == 1) {
			move_num = 2; // move_down
		}
		if (ReadKey4 == 1) {
			move_num = 1; // move_left
		}

		delay_num = delay_num + 1;

		if (delay_num == 5) {

			ST7735_DrawRect(after_tail.x0, after_tail.y0, after_tail.x1,
					after_tail.y1, ST7735_COLOR_WHITE);
			for (uint16_t i = 0; i < body_size; i++) {
				ST7735_DrawRect(body[i].x0, body[i].y0, body[i].x1, body[i].y1,
				ST7735_COLOR_GREEN);
			}
			ST7735_DrawRect(head.x0, head.y0, head.x1, head.y1,
					ST7735_COLOR_BLUE);

//	  uint8_t move_num = rand()%4;

			after_tail.x0 = body[0].x0;
			after_tail.y0 = body[0].y0;
			after_tail.x1 = body[0].x1;
			after_tail.y1 = body[0].y1;

			for (uint16_t i = 0; i < body_size - 1; i++) {
				body[i].x0 = body[i + 1].x0;
				body[i].y0 = body[i + 1].y0;
				body[i].x1 = body[i + 1].x1;
				body[i].y1 = body[i + 1].y1;
			}

			body[body_size - 1].x0 = head.x0;
			body[body_size - 1].y0 = head.y0;
			body[body_size - 1].x1 = head.x1;
			body[body_size - 1].y1 = head.y1;

			switch (move_num) {
			case 0: //move_right
				if (flag_move_left == false) {
					move_num_x0 = 5;
					move_num_x1 = 5;
					move_num_y0 = 0;
					move_num_y1 = 0;

					flag_move_right = true;
					flag_move_left = false;
					flag_move_down = false;
					flag_move_up = false;
				}
				break;
			case 1: //move_left
				if (flag_move_right == false) {
					move_num_x0 = -5;
					move_num_x1 = -5;
					move_num_y0 = 0;
					move_num_y1 = 0;

					flag_move_right = false;
					flag_move_left = true;
					flag_move_down = false;
					flag_move_up = false;
				}
				break;
			case 2: //move_down
				if (flag_move_up == false) {
					move_num_x0 = 0;
					move_num_x1 = 0;
					move_num_y0 = 5;
					move_num_y1 = 5;

					flag_move_right = false;
					flag_move_left = false;
					flag_move_down = true;
					flag_move_up = false;
				}
				break;
			case 3: //move_up
				if (flag_move_down == false) {
					move_num_x0 = 0;
					move_num_x1 = 0;
					move_num_y0 = -5;
					move_num_y1 = -5;

					flag_move_right = false;
					flag_move_left = false;
					flag_move_down = false;
					flag_move_up = true;
				}
				break;
			}

			head.x0 = head.x0 + move_num_x0;
			head.x1 = head.x1 + move_num_x1;
			head.y0 = head.y0 + move_num_y0;
			head.y1 = head.y1 + move_num_y1;

			game_over(head);

			delay_num = 0;
		}

		HAL_Delay(20);

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
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
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
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8,
			GPIO_PIN_RESET);

	/*Configure GPIO pins : move_up_Pin move_right_Pin move_down_Pin move_left_Pin */
	GPIO_InitStruct.Pin = move_up_Pin | move_right_Pin | move_down_Pin
			| move_left_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB6 PB7 PB8 */
	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
