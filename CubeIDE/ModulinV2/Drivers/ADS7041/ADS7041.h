#ifndef ADS7041_H
#define ADS7041_H

// Libraries
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_spi.h"
#include <math.h>

// ADC parameter struct
typedef struct {
    GPIO_TypeDef *csPort;
    uint16_t csPin;

    SPI_HandleTypeDef *spi;

    uint16_t raw;
    uint16_t result;
} ads7041;

// Function prototypes
// Getting the converted values from the ADC
HAL_StatusTypeDef GetADC7041(ads7041 adc);

#endif // __ADS7041_H__