#include "DS3502UP.h"

HAL_StatusTypeDef SetDS3502UP(ds3502up pot, uint8_t value) {
    HAL_StatusTypeDef status = HAL_OK;
    // Discard all but the first 7 bits
    value &= 0x7F;
    
    status = HAL_I2C_Master_Transmit(pot.i2c, pot.address, &value, sizeof(value), 100);

    return status;
}