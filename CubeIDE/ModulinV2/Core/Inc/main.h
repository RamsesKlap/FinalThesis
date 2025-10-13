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
#define LFO_CS_Pin GPIO_PIN_13
#define LFO_CS_GPIO_Port GPIOC
#define OSC1_Pin GPIO_PIN_0
#define OSC1_GPIO_Port GPIOH
#define OSC2_Pin GPIO_PIN_1
#define OSC2_GPIO_Port GPIOH
#define ENC_A_Pin GPIO_PIN_0
#define ENC_A_GPIO_Port GPIOA
#define ENC_B_Pin GPIO_PIN_1
#define ENC_B_GPIO_Port GPIOA
#define ENC_SW_Pin GPIO_PIN_2
#define ENC_SW_GPIO_Port GPIOA
#define ADC_CS1_Pin GPIO_PIN_4
#define ADC_CS1_GPIO_Port GPIOA
#define ADC_CLK_Pin GPIO_PIN_5
#define ADC_CLK_GPIO_Port GPIOA
#define ADC_MISO_Pin GPIO_PIN_6
#define ADC_MISO_GPIO_Port GPIOA
#define ADC_CS2_Pin GPIO_PIN_7
#define ADC_CS2_GPIO_Port GPIOA
#define DAC_CS1_Pin GPIO_PIN_12
#define DAC_CS1_GPIO_Port GPIOB
#define DAC_CLK_Pin GPIO_PIN_13
#define DAC_CLK_GPIO_Port GPIOB
#define DAC_CS2_Pin GPIO_PIN_14
#define DAC_CS2_GPIO_Port GPIOB
#define DAC_MOSI_Pin GPIO_PIN_15
#define DAC_MOSI_GPIO_Port GPIOB
#define SDA2_Pin GPIO_PIN_9
#define SDA2_GPIO_Port GPIOC
#define SCL2_Pin GPIO_PIN_8
#define SCL2_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define LFO_CLK_Pin GPIO_PIN_10
#define LFO_CLK_GPIO_Port GPIOC
#define LFO_MISO_Pin GPIO_PIN_11
#define LFO_MISO_GPIO_Port GPIOC
#define LFO_MOSI_Pin GPIO_PIN_12
#define LFO_MOSI_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_5
#define LED_B_GPIO_Port GPIOB
#define SCL1_Pin GPIO_PIN_6
#define SCL1_GPIO_Port GPIOB
#define SDA1_Pin GPIO_PIN_7
#define SDA1_GPIO_Port GPIOB
#define LED_R_Pin GPIO_PIN_8
#define LED_R_GPIO_Port GPIOB
#define LED_G_Pin GPIO_PIN_9
#define LED_G_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
