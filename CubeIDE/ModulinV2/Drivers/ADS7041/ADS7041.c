#include "ADS7041.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"

HAL_StatusTypeDef GetADC7041(ads7041 adc) {
    HAL_StatusTypeDef status;

    // Pull CS pin low
    HAL_GPIO_WritePin(adc.csPort, adc.csPin, 0);

    uint8_t buf[2] = {0x00, 0x00};
    HAL_Delay(1);

    // Receive unrefined data from the ADC chip
    status = HAL_SPI_TransmitReceive(adc.spi, buf, adc.raw, 2, 100);

    // Pull the CS back high
    HAL_GPIO_WritePin(adc.csPort, adc.csPin, 1);

    // In case of a failure, just set the result to 0
    if (status)
        adc.result = 0;
    else {
        adc.result = ((uint16_t)adc.raw[0] << 8) | adc.raw[1];
        adc.result = (adc.result >> 6) & 0x3FFF;
    }

    return status;
}