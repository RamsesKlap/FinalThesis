#include "DACx0501.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_spi.h"

// SPI writing helper function
HAL_StatusTypeDef _write(dacx0501 dac, uint8_t reg, uint16_t data) {
    HAL_StatusTypeDef status;

    // Make the register and data into one data array where:
    // 1st word - register address
    // 2nd word - 8 most significant bits of the data
    // 3rd word - 8 least significant bits of the data
    dac.data[0] = reg;
    dac.data[1] = (data >> 8) & 0xFF;
    dac.data[2] = data & 0xFF;

    // Manually pull the CS pin low
    HAL_GPIO_WritePin(dac.csPort, dac.csPin, 0);

    // Send the data array in blocking mode
    status = HAL_SPI_Transmit(dac.spi, dac.data, 3, 100);

    // Pull the CS back up high
    HAL_GPIO_WritePin(dac.csPort, dac.csPin, 1);

    return status;
}

HAL_StatusTypeDef ConfDACX051(dacx0501 dac) {
    HAL_StatusTypeDef status; 

    // Configure the DAC output to asynchronous mode
    // AKA make the output update immediately
    // Bit 0 -> 0
    status = _write(dac, SYNC, 0x0000);

    // Configure the DAC to turn off the internal reference
    // and not be in power down mode
    // Bit 8 -> 1, Bit 0 -> 0
    status = _write(dac, CONFIG, 0x0000);

    // Configure the DAC to divide the reference by 2 and
    // set the buffer gain to 2
    // Bits 8 & 0 -> 1
    status = _write(dac, GAIN, 0x0101);

    // Configure that the DAC is not in synchronous mode
    // Bit 4 -> 0
    status = _write(dac, TRIGGER, 0x0000);

    return status;
}

HAL_StatusTypeDef SetDACX0501(dacx0501 dac, uint16_t value) {
    HAL_StatusTypeDef status = HAL_OK; 

    // Discard all but the first 12 bits
    value &= 0xFFF;

    // Send the DAC value to the DAC output register
    status = _write(dac, DAC, value);

    return status;
}