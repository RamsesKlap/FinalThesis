#include "ADS7041.h"
#include "stm32f4xx_hal_spi.h"

HAL_StatusTypeDef GetADC7041(ads7041 adc) {
    HAL_StatusTypeDef status = HAL_OK;

    // Pull CS pin low
    HAL_GPIO_WritePin(adc.csPort, adc.csPin, 0);

    // Receive unrefined data from the ADC chip
    status = HAL_SPI_Receive(adc.spi, (uint8_t *)&adc.raw, 1, 100);

    // Pull the CS back high
    HAL_GPIO_WritePin(adc.csPort, adc.csPin, 1);

    // In case of a failure, just set the result to 0
    if (status)
        adc.result = 0;
    else
        adc.result = (adc.raw >> 2) & 0x3FFF;

    return status;
}