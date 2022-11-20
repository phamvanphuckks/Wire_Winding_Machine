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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "keypad.h"
#include "tb6600.h"
#include "hw_config.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// For key pad
char key = NON_KEY_RELEASED;
KEYPAD_t KeyPad;

char KEYMAP[NUMROWS][NUMCOLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

// For TB6600
static tb6600_t tb6600;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if ((htim->Instance == htim2.Instance) && (tb6600.en_stt == TB6600_ENABLE))
	{
		/* Toggle PA8 */
		HAL_GPIO_TogglePin(TB6600PUL_PORT, TB6600PUL);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

		tb6600.step_number++;
		if(tb6600.step_number >= (tb6600.pulse_per_rev * 2))
		{
			tb6600.rev_number_cur++;
			
			if(tb6600.number_of_rev_en == 1)
			{
				tb6600.number_of_rev_setup--;
				
				if(tb6600.number_of_rev_setup == 0)
				{
					tb6600_set_status(&tb6600, TB6600_DISABLE);
				}
			}
			
			tb6600.step_number = 0;
		}
	}
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
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	KEYPAD4X4_Init(&KeyPad, KEYMAP, KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN,
																	KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN,
																	KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN,
																	KEYPAD_ROW4_PORT, KEYPAD_ROW4_PIN,
                                  KEYPAD_COLUM1_PORT, KEYPAD_COLUM1_PIN,
	                                KEYPAD_COLUM2_PORT, KEYPAD_COLUM2_PIN,
																	KEYPAD_COLUM3_PORT, KEYPAD_COLUM3_PIN,
																	KEYPAD_COLUM4_PORT, KEYPAD_COLUM4_PIN);
																		
	tb6600_init(&tb6600, TB6600_ENABLE, TB6600_RIGHT_2_LEFT, PULSE_PER_REV_200);
	
  /*##-1- Start the TIM Base generation in interrupt mode ####################*/
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		key = KEYPAD4X4_scan(&KeyPad);
		if(key)
		{
			HAL_UART_Transmit(&huart1, (uint8_t*)&key, 1, 1000);
		}
		
		// turn right to left
		if(key == 'A')
		{
			tb6600_set_direction(&tb6600, TB6600_RIGHT_2_LEFT);
		}
		
		// turn left to right
		if(key == 'B')
		{
			tb6600_set_direction(&tb6600, TB6600_LEFT_2_RIGHT);
		}
		
		// Start
		if(key == 'C')
		{
			tb6600_set_status(&tb6600, TB6600_ENABLE);
		}
		
		// Pause
		if(key == 'D')
		{
			tb6600_set_status(&tb6600, TB6600_DISABLE);
		}
		
		// rpm
		if(key == '#')
		{
			tb6600.rpm += 10;
			tb6600_set_rpm(&tb6600, tb6600.rpm);
		}
		
		// setup the number of revolution
		if(key == '0')
		{
			tb6600_set_num_of_rev(&tb6600, 5, 1);
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
