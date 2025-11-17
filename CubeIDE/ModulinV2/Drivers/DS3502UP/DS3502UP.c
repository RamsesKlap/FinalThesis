#include "DS3502UP.h"
#include "stm32f4xx_hal_i2c.h"

HAL_StatusTypeDef SetDS3502UP(ds3502up* pot) {
    HAL_StatusTypeDef status;
    // Discard all but the first 7 bits
    pot->newValue &= 0x7F;
    
    uint8_t data[2] = {WIPER_R, pot->newValue};
    status = HAL_I2C_Master_Transmit(pot->i2c, pot->address, data, 2, 100);

    if (!status)
        pot->currentValue = pot->newValue;
    else
        pot->currentValue = 0;

    return status;
}

HAL_StatusTypeDef GetDS3502UP(ds3502up* pot) {
    HAL_StatusTypeDef status;

    uint8_t data;
    status = HAL_I2C_Master_Receive(pot->i2c, pot->address | 0b1, &data, 1, 100);

    if (!status)
        pot->currentValue = data;
    else
        pot->currentValue = 0;

    return status;
}