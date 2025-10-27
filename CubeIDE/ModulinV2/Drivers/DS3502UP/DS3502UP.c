#include "DS3502UP.h"

HAL_StatusTypeDef SetDS3502UP(ds3502up pot, uint8_t value) {
    HAL_StatusTypeDef status = HAL_OK;
    // Discard all but the first 7 bits
    value &= 0x7F;
    
    uint8_t data[2] = {WIPER_R, value};
    status = HAL_I2C_Master_Transmit(pot.i2c, pot.address, data, 2, 100);

    return status;
}