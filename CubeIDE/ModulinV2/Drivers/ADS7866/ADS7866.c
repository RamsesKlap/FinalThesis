#include "ADS7866.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_spi.h"

HAL_StatusTypeDef GetADS7866(ads7866* adc) {
    HAL_StatusTypeDef status;

    // Pull CS pin low
    HAL_GPIO_WritePin(adc->csPort, adc->csPin, 0);
    HAL_Delay(1);

    // Receive unrefined data from the ADC chip
    status = HAL_SPI_Receive(adc->spi, (uint8_t *)&adc->value, 1, 100);

    // Pull the CS back high
    HAL_GPIO_WritePin(adc->csPort, adc->csPin, 1);

    return status;
}