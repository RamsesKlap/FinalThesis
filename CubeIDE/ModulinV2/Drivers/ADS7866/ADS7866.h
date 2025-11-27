#ifndef ADS7866_H
#define ADS7866_H

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

    uint16_t value;
} ads7866;

// Function prototypes
// Getting the converted values from the ADC
HAL_StatusTypeDef GetADS7866(ads7866* adc);

#endif // __ADS7866_H__