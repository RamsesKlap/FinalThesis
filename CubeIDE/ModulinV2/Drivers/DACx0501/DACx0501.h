#ifndef DACX0501_H
#define DACX0501_H

// Libraries
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_spi.h"

// Register map
// Not a complete list as some registers are not used in SPI
#define SYNC    0x02
#define CONFIG  0x03
#define GAIN    0x04
#define TRIGGER 0x05
#define DAC     0x08

// DAC parameter struct
typedef struct {
    GPIO_TypeDef *csPort;
    uint16_t csPin;

    SPI_HandleTypeDef *spi;

    uint16_t currentValue;
    uint16_t newValue;
} dacx0501;

// Function prototypes
// Configuration of the DAC
HAL_StatusTypeDef ConfDACX051(dacx0501* dac);

// Sending of output value to the DAC
HAL_StatusTypeDef SetDACX0501(dacx0501 *dac);

#endif // __DACX0501_H__