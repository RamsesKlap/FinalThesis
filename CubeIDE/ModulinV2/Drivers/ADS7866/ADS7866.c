#include "ADS7866.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"

uint16_t GetADC7041(ads7866 adc) {
    uint16_t raw;

    // Pull CS pin low
    HAL_GPIO_WritePin(adc.csPort, adc.csPin, 0);
    HAL_Delay(1);

    // Receive unrefined data from the ADC chip
    HAL_SPI_Receive(adc.spi, (uint8_t *)&raw, 1, 100);

    // Pull the CS back high
    HAL_GPIO_WritePin(adc.csPort, adc.csPin, 1);

    return raw;
}