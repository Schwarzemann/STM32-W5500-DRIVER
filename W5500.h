#ifndef W5500_H
#define W5500_H

#include "stm32f4xx_hal.h"  // Adjust for your STM32 model

class W5500 {
public:
    W5500(SPI_HandleTypeDef *hspi, GPIO_TypeDef *csPort, uint16_t csPin);
    bool initialize();
    
    uint8_t readRegister(uint16_t address);
    void writeRegister(uint16_t address, uint8_t value);

protected:
    SPI_HandleTypeDef *spiHandle;
    GPIO_TypeDef *csPort;
    uint16_t csPin;

    void select();
    void deselect();
    uint8_t spiTransfer(uint8_t data);
};

#endif // W5500_H
