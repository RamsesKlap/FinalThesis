#ifndef DACX0501_H
#define DACX0501_H

// Libraries
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_spi.h"

// Register map
#define NOOP    0x00
#define DEVID   0x01 
#define SYNC    0x02
#define CONFIG  0x03
#define GAIN    0x04
#define TRIGGER 0x05
#define STATUS  0x06
#define DAC     0x07

// DAC parameter struct
typedef struct {
    GPIO_TypeDef *csPort;
    uint16_t csPin;

    SPI_HandleTypeDef *spi;

    uint8_t data[3];
} dacx0501;

// Function prototypes
// Configuration to set the internal reference off and not have it in power-down mode
HAL_StatusTypeDef ConfDACX051(dacx0501 dac);

// Sending of output value to the DAC
HAL_StatusTypeDef SetDACX0501(dacx0501 dac, uint16_t value);

#endif // __DACX0501_H__