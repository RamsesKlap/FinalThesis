#include "DACx0501.h"

HAL_StatusTypeDef ConfDACX051(dacx0501 dac) {
    HAL_StatusTypeDef status = HAL_OK; 

    // Adressing the CONFIG register
    dac.data[0] = CONFIG;
    // Bit8 - 1 (No internal reference)
    dac.data[1] = 0x01;
    // Bit0 - 0 (Not in power-down mode) 
    dac.data[2] = 0x00;

    // Pull CS pin low
    HAL_GPIO_WritePin(dac.csPort, dac.csPin, 0);

    // Send configuration data to DAC
    status = HAL_SPI_Transmit(dac.spi, dac.data, 3, 100);

    // Pull CS pin back high
    HAL_GPIO_WritePin(dac.csPort, dac.csPin, 1);

    return status;
}

HAL_StatusTypeDef SetDACX0501(dacx0501 dac, uint16_t value) {
    HAL_StatusTypeDef status = HAL_OK; 

    // Discard all but the first 12 bits
    value &= 0xFFF;

    // Adressing the CONFIG register
    dac.data[0] = DAC;
    // Bits15-12 - 0000, Bits 11-8 - first 4 MSBs
    dac.data[1] = (value & 0xF00) >> 8;
    // Bit7-0 - The rest of the value 
    dac.data[2] = (value & 0xFF);

    // Pull CS pin low
    HAL_GPIO_WritePin(dac.csPort, dac.csPin, 0);

    // Send configuration data to DAC
    status = HAL_SPI_Transmit(dac.spi, dac.data, 3, 100);

    // Pull CS pin back high
    HAL_GPIO_WritePin(dac.csPort, dac.csPin, 1);

    return status;
}