/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LFO_SPI_CLK_Pin GPIO_PIN_2
#define LFO_SPI_CLK_GPIO_Port GPIOE
#define LFO_SPI_CS_Pin GPIO_PIN_4
#define LFO_SPI_CS_GPIO_Port GPIOE
#define LFO_SPI_MISO_Pin GPIO_PIN_5
#define LFO_SPI_MISO_GPIO_Port GPIOE
#define LFO_SPI_MOSI_Pin GPIO_PIN_6
#define LFO_SPI_MOSI_GPIO_Port GPIOE
#define RIBBON_ADC_SPI_CS1_Pin GPIO_PIN_4
#define RIBBON_ADC_SPI_CS1_GPIO_Port GPIOA
#define RIBBON_ADC_SPI_CLK_Pin GPIO_PIN_5
#define RIBBON_ADC_SPI_CLK_GPIO_Port GPIOA
#define RIBBON_ADC_SPI_MISO_Pin GPIO_PIN_6
#define RIBBON_ADC_SPI_MISO_GPIO_Port GPIOA
#define RIBBON_ADC_SPI_CS2_Pin GPIO_PIN_7
#define RIBBON_ADC_SPI_CS2_GPIO_Port GPIOA
#define RIBBON_DAC_SPI_CS1_Pin GPIO_PIN_12
#define RIBBON_DAC_SPI_CS1_GPIO_Port GPIOB
#define RIBBON_DAC_SPI_CLK_Pin GPIO_PIN_13
#define RIBBON_DAC_SPI_CLK_GPIO_Port GPIOB
#define RIBBON_DAC_SPI_CS2_Pin GPIO_PIN_14
#define RIBBON_DAC_SPI_CS2_GPIO_Port GPIOB
#define RIBBON_DAC_MOSI_Pin GPIO_PIN_15
#define RIBBON_DAC_MOSI_GPIO_Port GPIOB
#define ADSR_SPI_CLK_Pin GPIO_PIN_10
#define ADSR_SPI_CLK_GPIO_Port GPIOC
#define ADSR_SPI_CS2_Pin GPIO_PIN_11
#define ADSR_SPI_CS2_GPIO_Port GPIOC
#define ADSR_SPI_MOSI_Pin GPIO_PIN_12
#define ADSR_SPI_MOSI_GPIO_Port GPIOC
#define ADSR_SPI_CS1_Pin GPIO_PIN_0
#define ADSR_SPI_CS1_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
