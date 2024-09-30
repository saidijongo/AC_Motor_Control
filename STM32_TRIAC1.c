/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
uint16_t alpha_lut[] = { 10000, 9465, 9325, 9227, 9148, 9082, 9024, 8972, 8924, 8880, 8840, 8801,
8765, 8731, 8699, 8668, 8638, 8610, 8582, 8556, 8530, 8505, 8481, 8458, 8435, 8413, 8391, 8370,
8350, 8330, 8310, 8291, 8272, 8253, 8235, 8217, 8199, 8182, 8165, 8148, 8132, 8116, 8100, 8084,
8069, 8053, 8038, 8023, 8009, 7994, 7980, 7966, 7952, 7938, 7924, 7911, 7897, 7884, 7871, 7858,
7845, 7833, 7820, 7808, 7795, 7783, 7771, 7759, 7747, 7735, 7724, 7712, 7701, 7689, 7678, 7667,
7656, 7645, 7634, 7623, 7612, 7601, 7591, 7580, 7569, 7559, 7549, 7538, 7528, 7518, 7508, 7498,
7488, 7478, 7468, 7458, 7449, 7439, 7429, 7420, 7410, 7401, 7392, 7382, 7373, 7364, 7355, 7345,
7336, 7327, 7318, 7309, 7300, 7292, 7283, 7274, 7265, 7256, 7248, 7239, 7231, 7222, 7214, 7205,
7197, 7188, 7180, 7172, 7163, 7155, 7147, 7139, 7131, 7122, 7114, 7106, 7098, 7090, 7082, 7074,
7066, 7059, 7051, 7043, 7035, 7027, 7020, 7012, 7004, 6997, 6989, 6982, 6974, 6966, 6959, 6951,
6944, 6936, 6929, 6922, 6914, 6907, 6900, 6892, 6885, 6878, 6871, 6863, 6856, 6849, 6842, 6835,
6828, 6821, 6814, 6806, 6799, 6792, 6785, 6778, 6772, 6765, 6758, 6751, 6744, 6737, 6730, 6723,
6717, 6710, 6703, 6696, 6690, 6683, 6676, 6670, 6663, 6656, 6650, 6643, 6636, 6630, 6623, 6617,
6610, 6604, 6597, 6591, 6584, 6578, 6571, 6565, 6558, 6552, 6545, 6539, 6533, 6526, 6520, 6514,
6507, 6501, 6495, 6488, 6482, 6476, 6470, 6463, 6457, 6451, 6445, 6439, 6432, 6426, 6420, 6414,
6408, 6402, 6396, 6390, 6383, 6377, 6371, 6365, 6359, 6353, 6347, 6341, 6335, 6329, 6323, 6317,
6311, 6305, 6299, 6293, 6288, 6282, 6276, 6270, 6264, 6258, 6252, 6246, 6240, 6235, 6229, 6223,
6217, 6211, 6206, 6200, 6194, 6188, 6182, 6177, 6171, 6165, 6160, 6154, 6148, 6142, 6137, 6131,
6125, 6120, 6114, 6108, 6103, 6097, 6091, 6086, 6080, 6074, 6069, 6063, 6058, 6052, 6046, 6041,
6035, 6030, 6024, 6019, 6013, 6008, 6002, 5996, 5991, 5985, 5980, 5974, 5969, 5963, 5958, 5952,
5947, 5942, 5936, 5931, 5925, 5920, 5914, 5909, 5903, 5898, 5893, 5887, 5882, 5876, 5871, 5866,
5860, 5855, 5849, 5844, 5839, 5833, 5828, 5823, 5817, 5812, 5807, 5801, 5796, 5791, 5785, 5780,
5775, 5769, 5764, 5759, 5753, 5748, 5743, 5738, 5732, 5727, 5722, 5717, 5711, 5706, 5701, 5695,
5690, 5685, 5680, 5675, 5669, 5664, 5659, 5654, 5648, 5643, 5638, 5633, 5628, 5622, 5617, 5612,
5607, 5602, 5596, 5591, 5586, 5581, 5576, 5571, 5565, 5560, 5555, 5550, 5545, 5540, 5535, 5529,
5524, 5519, 5514, 5509, 5504, 5499, 5493, 5488, 5483, 5478, 5473, 5468, 5463, 5458, 5453, 5447,
5442, 5437, 5432, 5427, 5422, 5417, 5412, 5407, 5402, 5397, 5391, 5386, 5381, 5376, 5371, 5366,
5361, 5356, 5351, 5346, 5341, 5336, 5331, 5326, 5321, 5316, 5310, 5305, 5300, 5295, 5290, 5285,
5280, 5275, 5270, 5265, 5260, 5255, 5250, 5245, 5240, 5235, 5230, 5225, 5220, 5215, 5210, 5205,
5200, 5195, 5190, 5185, 5180, 5175, 5170, 5165, 5160, 5155, 5150, 5145, 5140, 5135, 5130, 5125,
5120, 5115, 5110, 5105, 5100, 5095, 5090, 5085, 5080, 5075, 5070, 5065, 5060, 5055, 5050, 5045,
5040, 5035, 5030, 5025, 5020, 5015, 5010, 5005, 5000, 4994, 4989, 4984, 4979, 4974, 4969, 4964,
4959, 4954, 4949, 4944, 4939, 4934, 4929, 4924, 4919, 4914, 4909, 4904, 4899, 4894, 4889, 4884,
4879, 4874, 4869, 4864, 4859, 4854, 4849, 4844, 4839, 4834, 4829, 4824, 4819, 4814, 4809, 4804,
4799, 4794, 4789, 4784, 4779, 4774, 4769, 4764, 4759, 4754, 4749, 4744, 4739, 4734, 4729, 4724,
4719, 4714, 4709, 4704, 4699, 4694, 4689, 4683, 4678, 4673, 4668, 4663, 4658, 4653, 4648, 4643,
4638, 4633, 4628, 4623, 4618, 4613, 4608, 4602, 4597, 4592, 4587, 4582, 4577, 4572, 4567, 4562,
4557, 4552, 4546, 4541, 4536, 4531, 4526, 4521, 4516, 4511, 4506, 4500, 4495, 4490, 4485, 4480,
4475, 4470, 4464, 4459, 4454, 4449, 4444, 4439, 4434, 4428, 4423, 4418, 4413, 4408, 4403, 4397,
4392, 4387, 4382, 4377, 4371, 4366, 4361, 4356, 4351, 4345, 4340, 4335, 4330, 4324, 4319, 4314,
4309, 4304, 4298, 4293, 4288, 4282, 4277, 4272, 4267, 4261, 4256, 4251, 4246, 4240, 4235, 4230,
4224, 4219, 4214, 4208, 4203, 4198, 4192, 4187, 4182, 4176, 4171, 4166, 4160, 4155, 4150, 4144,
4139, 4133, 4128, 4123, 4117, 4112, 4106, 4101, 4096, 4090, 4085, 4079, 4074, 4068, 4063, 4057,
4052, 4047, 4041, 4036, 4030, 4025, 4019, 4014, 4008, 4003, 3997, 3991, 3986, 3980, 3975, 3969,
3964, 3958, 3953, 3947, 3941, 3936, 3930, 3925, 3919, 3913, 3908, 3902, 3896, 3891, 3885, 3879,
3874, 3868, 3862, 3857, 3851, 3845, 3839, 3834, 3828, 3822, 3817, 3811, 3805, 3799, 3793, 3788,
3782, 3776, 3770, 3764, 3759, 3753, 3747, 3741, 3735, 3729, 3723, 3717, 3711, 3706, 3700, 3694,
3688, 3682, 3676, 3670, 3664, 3658, 3652, 3646, 3640, 3634, 3628, 3622, 3616, 3609, 3603, 3597,
3591, 3585, 3579, 3573, 3567, 3560, 3554, 3548, 3542, 3536, 3529, 3523, 3517, 3511, 3504, 3498,
3492, 3485, 3479, 3473, 3466, 3460, 3454, 3447, 3441, 3434, 3428, 3421, 3415, 3408, 3402, 3395,
3389, 3382, 3376, 3369, 3363, 3356, 3349, 3343, 3336, 3329, 3323, 3316, 3309, 3303, 3296, 3289,
3282, 3276, 3269, 3262, 3255, 3248, 3241, 3234, 3227, 3221, 3214, 3207, 3200, 3193, 3185, 3178,
3171, 3164, 3157, 3150, 3143, 3136, 3128, 3121, 3114, 3107, 3099, 3092, 3085, 3077, 3070, 3063,
3055, 3048, 3040, 3033, 3025, 3017, 3010, 3002, 2995, 2987, 2979, 2972, 2964, 2956, 2948, 2940,
2933, 2925, 2917, 2909, 2901, 2893, 2885, 2877, 2868, 2860, 2852, 2844, 2836, 2827, 2819, 2811,
2802, 2794, 2785, 2777, 2768, 2760, 2751, 2743, 2734, 2725, 2716, 2707, 2699, 2690, 2681, 2672,
2663, 2654, 2644, 2635, 2626, 2617, 2607, 2598, 2589, 2579, 2570, 2560, 2550, 2541, 2531, 2521,
2511, 2501, 2491, 2481, 2471, 2461, 2450, 2440, 2430, 2419, 2408, 2398, 2387, 2376, 2365, 2354,
2343, 2332, 2321, 2310, 2298, 2287, 2275, 2264, 2252, 2240, 2228, 2216, 2204, 2191, 2179, 2166,
2154, 2141, 2128, 2115, 2102, 2088, 2075, 2061, 2047, 2033, 2019, 2005, 1990, 1976, 1961, 1946,
1930, 1915, 1899, 1883, 1867, 1851, 1834, 1817, 1800, 1782, 1764, 1746, 1727, 1708, 1689, 1669,
1649, 1629, 1608, 1586, 1564, 1541, 1518, 1494, 1469, 1443, 1417, 1389, 1361, 1331, 1300, 1268,
1234, 1198, 1159, 1119, 1075, 1027, 975, 917, 851, 772, 674, 534, 0 };

#define TRIAC_PULSE_WIDTH  100  // Duration of TRIAC trigger pulse in �s

void timer1_init( void )
{
   __HAL_RCC_TIM1_CLK_ENABLE(); // Enable Timer 1 clock
   TIM1->CR1   = 0x0088;        // Auto-reload, One-Pulse-Mode 
   TIM1->CR2   = 0x0000;        // Idle-state configuration
   TIM1->SMCR  = 0x0066;        // Trigger-Mode, Timer input 2
   TIM1->DIER  = 0x0000;        // Disable interrupts
   TIM1->SR    = 0x0000;        // Clear status register
   TIM1->EGR   = 0x0000;        // Clear event generation register
   TIM1->CCMR1 = 0x0178;        // OC1: PWM2-Mode, Preload, IC2: IC2 on TI2
   TIM1->CCMR2 = 0x0000;        // OC3/OC4, IC3/IC4 off
   TIM1->CCER  = 0x00A1;        // OC1: On, AH; IC2: On, Both edges  
   TIM1->CNT   = 0;             // Clear timer 1 counter
   TIM1->PSC   = 168-1;         // Set prescaler to 168
   TIM1->ARR   = 0x0000;        // Initialize Auto-reload register
   TIM1->RCR   = 0x0000;        // Clear repetition counter     
   TIM1->CCR1  = 0x0000;        // Initialize Capture/Compare register 1
   TIM1->CCR2  = 0x0000;        // Clear Capture/Compare register 2
   TIM1->CCR3  = 0x0000;        // Clear Capture/Compare register 3
   TIM1->CCR4  = 0x0000;        // Clear Capture/Compare register 4
   TIM1->BDTR  = 0x8000;        // Main output enable
   TIM1->DCR   = 0x0000;        // Clear DMA configuration (DMA not needed)
   // TIM1->DMAR = ......;      // DO NOT WRITE TO THIS REGISTER!
   TIM1->CR1  |= 0x0001;        // Timer 1 Enable
}

void gpio_init( void )
{
   __HAL_RCC_GPIOE_CLK_ENABLE();    // Enable GPIOE clock
   GPIOE->MODER   = 0x00880000;     // Enable PE9/PE11 alternate function mode
   GPIOE->AFR[1]  = 0x00001010;     // Select PE9/PE11 alternate function AF1
   GPIOE->AFR[0]  = 0x00000000;     // Clear AFRL
   GPIOE->OTYPER  = 0x00000000;     // Set all outputs to push-pull mode (default)
   GPIOE->OSPEEDR = 0x00000000;     // Set all outputs to low-speed (default)
   GPIOE->PUPDR   = 0x00000000;     // Disable all pull-ups and pull-downs
}


void set_alpha( int alpha )
{
   TIM1->CCR1 = alpha;
   TIM1->ARR = alpha + TRIAC_PULSE_WIDTH;     
}

void SystemClock_Config(void);

int main( void )
{
   int alpha, power;
   HAL_Init();                    // Initialize STM32 HAL
   SystemClock_Config();          // Configure core clock
   timer1_init();                 // Initialize Timer 1 (OC1 / IC2) 
   gpio_init();                   // Initialize GPIOs
   
   power = 500;                   // Set output power (1000=100%)
   alpha = alpha_lut[ power ];    // Get alpha from LUT
   set_alpha( alpha );            // Generate alpha on output 

   while( 1 );
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
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
