/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "ADS7866.h"
#include "DACx0501.h"
#include "DS3502UP.h"
#include "ssd1306_fonts.h"
#include "ssd1306_tests.h"
#include "usbd_cdc_if.h"
#include "usbd_def.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
  OCTAVE = 12,
  OCTAVE2 = 24,
  MAJOR = 16
  // MINOR = 16
} scaleMode;

typedef enum {
  MAIN,
  TUNE,
  ADSR,
  INTERFACE,
  LFO,
  TEST
} page;

typedef enum {
  BROWSE,
  EDIT
} uiState;

typedef enum {
  UP,
  DOWN
} direction;

typedef struct {
  page previousMenu;
  page currentMenu;
  uint8_t previousIndex;
  uint8_t selectionIndex;

  uiState state;
} menu;

typedef struct {
  uint32_t lastCounterValue;
  int32_t parameterValueModifier;
  direction dir;
} encoder;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define FONT Font_7x10
#define CURSOR_PAD 10
#define MENU_IDX_MAX 4
#define PARAM_MOD_MAX 0xFF

#define MEMBRANE_MAX 4095
#define MEMBRANE_MIN 0

#define DNL 1500
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c3;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim2;

osThreadId userInterfaceHandle;
osThreadId ADCHandle;
osThreadId DACHandle;
osThreadId digiPotHandle;
osThreadId encoderHandle;
/* USER CODE BEGIN PV */

char buffer[256];

// ADSR Digipot init.
ds3502up attack = {&hi2c3, ADDR1};
ds3502up decay = {&hi2c3, ADDR2};
ds3502up sustain = {&hi2c3, ADDR3};
ds3502up release = {&hi2c3, ADDR4};

// Tuning Digipot init.
ds3502up coarse1 = {&hi2c1, ADDR1, 0, 0};
ds3502up coarse2 = {&hi2c1, ADDR2, 0, 0};
ds3502up fine1 = {&hi2c1, ADDR3, 0, 0};
ds3502up fine2 = {&hi2c1, ADDR4, 0, 0};

// Interface input and output init.
ads7866 membrane1 = {ADC_CS1_GPIO_Port, ADC_CS1_Pin, &hspi1};
ads7866 membrane2 = {ADC_CS2_GPIO_Port, ADC_CS2_Pin, &hspi1};
dacx0501 pitchCV1 = {DAC_CS1_GPIO_Port, DAC_CS1_Pin, &hspi2};
dacx0501 pitchCV2 = {DAC_CS2_GPIO_Port, DAC_CS2_Pin, &hspi2};

menu oled = {TEST, MAIN, 1, 0, BROWSE};
encoder knob = {0, 0, UP};

// Current output mode
// mode outputMode = OCTAVE;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C3_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM2_Init(void);
void userInterface_Init(void const * argument);
void ADC_Init(void const * argument);
void DAC_Init(void const * argument);
void digiPot_Init(void const * argument);
void encoder_Init(void const * argument);

/* USER CODE BEGIN PFP */
void RGB(uint8_t red, uint8_t green, uint8_t blue);
void PeriphInit(void);
void USBWrite(unsigned char* msg);
void OLEDWrite(char* msg, uint8_t x, uint8_t y);
void ChangeMenu(page select);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C1_Init();
  MX_I2C3_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  PeriphInit();

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of userInterface */
  osThreadDef(userInterface, userInterface_Init, osPriorityNormal, 0, 128);
  userInterfaceHandle = osThreadCreate(osThread(userInterface), NULL);

  /* definition and creation of ADC */
  osThreadDef(ADC, ADC_Init, osPriorityHigh, 0, 128);
  ADCHandle = osThreadCreate(osThread(ADC), NULL);

  /* definition and creation of DAC */
  osThreadDef(DAC, DAC_Init, osPriorityAboveNormal, 0, 128);
  DACHandle = osThreadCreate(osThread(DAC), NULL);

  /* definition and creation of digiPot */
  osThreadDef(digiPot, digiPot_Init, osPriorityNormal, 0, 128);
  digiPotHandle = osThreadCreate(osThread(digiPot), NULL);

  /* definition and creation of encoder */
  osThreadDef(encoder, encoder_Init, osPriorityAboveNormal, 0, 128);
  encoderHandle = osThreadCreate(osThread(encoder), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

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
  hspi1.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
  hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
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
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
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
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LFO_CS_GPIO_Port, LFO_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ADC_CS1_Pin|ADC_CS2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DAC_CS1_Pin|DAC_CS2_Pin|LED_B_Pin|LED_R_Pin
                          |LED_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LFO_CS_Pin */
  GPIO_InitStruct.Pin = LFO_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LFO_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ENC_SW_Pin */
  GPIO_InitStruct.Pin = ENC_SW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ENC_SW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ADC_CS1_Pin ADC_CS2_Pin */
  GPIO_InitStruct.Pin = ADC_CS1_Pin|ADC_CS2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DAC_CS1_Pin DAC_CS2_Pin LED_B_Pin LED_R_Pin
                           LED_G_Pin */
  GPIO_InitStruct.Pin = DAC_CS1_Pin|DAC_CS2_Pin|LED_B_Pin|LED_R_Pin
                          |LED_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// Allows the switching of LED pins with one function
void RGB(uint8_t red, uint8_t green, uint8_t blue) {
  HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, red);
  HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, green);
  HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, blue);
}

void USBWrite(unsigned char* msg) {
  CDC_Transmit_FS(msg, strlen((char*)msg));
}

void OLEDWrite(char* msg, uint8_t x, uint8_t y) {
  ssd1306_SetCursor(x, y);
  ssd1306_WriteString(msg, FONT, White);
}

void PeriphInit(void) {
  // Turn off all the LEDs
  RGB(1, 1, 1);

  // SPI: Set all the CS pins to High
  HAL_GPIO_WritePin(ADC_CS1_GPIO_Port, ADC_CS1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(ADC_CS2_GPIO_Port, ADC_CS2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(DAC_CS1_GPIO_Port, DAC_CS1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(DAC_CS2_GPIO_Port, DAC_CS2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LFO_CS_GPIO_Port, LFO_CS_Pin, GPIO_PIN_SET);

  // Start timer peripheral for counting encoder ticks
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);

  // Initialize the OLED for debugging and UI
  ssd1306_Init();

  // Configure the DACs
  ConfDACX051(&pitchCV1);
  ConfDACX051(&pitchCV2);

  // Get the values the digipots are at
  GetDS3502UP(&coarse1);
  GetDS3502UP(&coarse2);
  GetDS3502UP(&fine1);
  GetDS3502UP(&fine2);
}

void ChangeMenu(page select) {
  // Delete previous menu
  ssd1306_Fill(Black);

  // Show the fields of the given menu
  switch (select) {
    case MAIN:  
      OLEDWrite("Tuning", CURSOR_PAD, 0);
      OLEDWrite("ADSR", CURSOR_PAD, 10);
      OLEDWrite("Interface", CURSOR_PAD, 20);
      OLEDWrite("LFO", CURSOR_PAD, 30);
      OLEDWrite("DEBUG", CURSOR_PAD, 40);
      break;

    case TUNE:
      OLEDWrite("BACK", CURSOR_PAD, 0);
      OLEDWrite("Coarse 1", CURSOR_PAD, 10);
      OLEDWrite("Fine 1", CURSOR_PAD, 20);
      OLEDWrite("Coarse 2", CURSOR_PAD, 30);
      OLEDWrite("Fine 2", CURSOR_PAD, 40);
      break;

    case ADSR:
      OLEDWrite("BACK", CURSOR_PAD, 0);
      OLEDWrite("Attack", CURSOR_PAD, 10);
      OLEDWrite("Decay", CURSOR_PAD, 20);
      OLEDWrite("Sustain", CURSOR_PAD, 30);
      OLEDWrite("Release", CURSOR_PAD, 40);
      break;

    case INTERFACE:
      OLEDWrite("BACK", CURSOR_PAD, 0);
      OLEDWrite("Mode", CURSOR_PAD, 10);
      OLEDWrite("A", CURSOR_PAD, 20);
      OLEDWrite("A", CURSOR_PAD, 30);
      OLEDWrite("A", CURSOR_PAD, 40);
      break;

    case LFO:
      OLEDWrite("BACK", CURSOR_PAD, 0);
      OLEDWrite("A", CURSOR_PAD, 10);
      OLEDWrite("A", CURSOR_PAD, 20);
      OLEDWrite("A", CURSOR_PAD, 30);
      OLEDWrite("A", CURSOR_PAD, 40);
      break;

    case TEST:
      OLEDWrite("BACK", CURSOR_PAD, 0);
      break;

    default:
      break;
  }
  ssd1306_UpdateScreen();

  oled.currentMenu = select;
}


uint16_t Map(uint16_t x, int step) {
	// x * step / (MEMBRANE_MAX - MEMBRANE_MAX) + out_min;
	return x * step / (MEMBRANE_MAX - MEMBRANE_MIN);
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_userInterface_Init */
/**
  * @brief  Function implementing the userInterface thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_userInterface_Init */
void userInterface_Init(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 5 */

  /* Infinite loop */
  for(;;) 
  {
    switch (oled.state) {
      case BROWSE:
        if (oled.previousMenu != oled.currentMenu) {
          ChangeMenu(oled.currentMenu);

          ssd1306_FillRectangle(0, 0, 10, 50, Black);
          if (oled.currentMenu == MAIN)
            ssd1306_FillCircle(5, 5 + 10 * (oled.previousMenu - 1), 3, White);
          else {
            ssd1306_FillCircle(5, 5, 3, White);
            oled.selectionIndex = 0;
          }
          ssd1306_UpdateScreen();

          oled.previousMenu = oled.currentMenu;
        }

        if (oled.previousIndex != oled.selectionIndex) {
          ssd1306_FillRectangle(0, 0, 10, 50, Black);
          ssd1306_FillCircle(5, 5 + 10 * oled.selectionIndex, 3, White);
          ssd1306_UpdateScreen();
          oled.previousIndex = oled.selectionIndex;
        }
        break;
      case EDIT:
        
        break;
    }
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_ADC_Init */
/**
* @brief Function implementing the ADC thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ADC_Init */
void ADC_Init(void const * argument)
{
  /* USER CODE BEGIN ADC_Init */
  /* Infinite loop */
  for(;;)
  {
    //GetADC7866(&membrane1);
    //GetADC7866(&membrane2);
    osDelay(1);
  }
  /* USER CODE END ADC_Init */
}

/* USER CODE BEGIN Header_DAC_Init */
/**
* @brief Function implementing the DAC thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DAC_Init */
void DAC_Init(void const * argument)
{
  /* USER CODE BEGIN DAC_Init */
  /* Infinite loop */
  for(;;)
  {
    // if (pitchCV1.currentValue != pitchCV1.newValue)
      //SetDACX0501(&pitchCV1);

    // if (pitchCV2.currentValue != pitchCV2.newValue)
      //SetDACX0501(&pitchCV2);

    osDelay(1);
  }
  /* USER CODE END DAC_Init */
}

/* USER CODE BEGIN Header_digiPot_Init */
/**
* @brief Function implementing the digiPot thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_digiPot_Init */
void digiPot_Init(void const * argument)
{
  /* USER CODE BEGIN digiPot_Init */
  /* Infinite loop */
  for(;;)
  { 
    if (coarse1.newValue != coarse1.currentValue)
      SetDS3502UP(&coarse1);

    if (coarse2.newValue != coarse2.currentValue)
      SetDS3502UP(&coarse2);

    if (fine1.newValue != fine1.currentValue)
      SetDS3502UP(&fine1);

    if (fine2.newValue != fine2.currentValue)
      SetDS3502UP(&fine2);

    osDelay(1);
  }
  /* USER CODE END digiPot_Init */
}

/* USER CODE BEGIN Header_encoder_Init */
/**
* @brief Function implementing the encoder thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_encoder_Init */
void encoder_Init(void const * argument)
{
  /* USER CODE BEGIN encoder_Init */
  uint32_t currentCounterValue;
  uint8_t pressed = 0;
  
  /* Infinite loop */
  for(;;)
  {
    currentCounterValue = (TIM2->CNT) >> 1;

    if (currentCounterValue != knob.lastCounterValue) {
      // Get whether the direction bit of the ControlRegister1 indicates
      // an up or down movement
      knob.dir = (TIM2->CR1 & TIM_CR1_DIR) ? DOWN: UP;

      switch (oled.state) {
        // Mode where you're navigating the menus
        case BROWSE:
          // Based on whether the direction was down or up, change the 
          // selection index accordingly
          if (knob.dir == UP) {
            if (oled.selectionIndex + 1 <= MENU_IDX_MAX)
              oled.selectionIndex++;
          }
          else {
            if (oled.selectionIndex - 1 >= 0)
              oled.selectionIndex--;
          }
          break;

        // Mode where you're changing the parameter value
        case EDIT:
          if (knob.dir == UP) 
            knob.parameterValueModifier++;
          else
            knob.parameterValueModifier--;
          break;
      }

      knob.lastCounterValue = currentCounterValue;
    }

    if (HAL_GPIO_ReadPin(ENC_SW_GPIO_Port, ENC_SW_Pin) && !pressed) {
      if (oled.currentMenu == MAIN) {
        oled.currentMenu = oled.selectionIndex + 1;
      }
      else {
        if (oled.selectionIndex == 0) {
          oled.currentMenu = MAIN;
        }
        else {
          knob.parameterValueModifier = 0;
          oled.state ^= EDIT;
        }
      }
      // Latch the pressed value to 1 so that it doesn't keep toggling
      pressed = 1;
    }
    else if (!HAL_GPIO_ReadPin(ENC_SW_GPIO_Port, ENC_SW_Pin)) {
      // Unlatch the button press
      pressed = 0;
    }
    
    osDelay(1);
  }
  /* USER CODE END encoder_Init */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
#ifdef USE_FULL_ASSERT
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
