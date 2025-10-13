#include "ADS7041.h"

HAL_StatusTypeDef GetADC7041(ads7041 adc) {
    HAL_StatusTypeDef status = HAL_OK;

    // Pull CS pin low
    HAL_GPIO_WritePin(adc.csPort, adc.csPin, 0);

    // Receive unrefined data from the ADC chip
    status = HAL_SPI_Receive(adc.spi, adc.buffer, 2, 100);

    // Pull the CS back high
    HAL_GPIO_WritePin(adc.csPort, adc.csPin, 1);

    // In case of a failure, just set the result to 0
    if (status != HAL_OK)
        adc.result = 0;
    else
        adc.result = (uint16_t)adc.buffer[0];

    return status;
}