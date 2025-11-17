#ifndef DS3502UP_H
#define DS3502UP_H

// Libraries
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_i2c.h"

// Register map
#define WIPER_R 0x00
#define CTRL_R  0x02

// All possible addressed for the potentiometers
typedef enum {
    ADDR1 = 0x50,
    ADDR2 = 0x52,
    ADDR3 = 0x54,
    ADDR4 = 0x56
} addr;

// Struct for holding the coms lines and the address
typedef struct {
    I2C_HandleTypeDef *i2c;
    addr address;

    uint8_t currentValue;
    uint8_t newValue;
} ds3502up;

// Prototypes
HAL_StatusTypeDef SetDS3502UP(ds3502up* pot);
HAL_StatusTypeDef GetDS3502UP(ds3502up* pot);

#endif // __DS3502UP_H__