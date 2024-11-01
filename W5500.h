#ifndef W5500_H
#define W5500_H

#include "stm32f4xx_hal.h"  // Change this according to your STM32 model

class W5500 {
public:
    W5500(SPI_HandleTypeDef *hspi, GPIO_TypeDef *csPort, uint16_t csPin);

    bool initialize();
    void setIPAddress(uint8_t ip[4]);
    void setGatewayAddress(uint8_t gateway[4]);
    void setSubnetMask(uint8_t subnet[4]);
    void setMACAddress(uint8_t mac[6]);

    // Additional functions for socket handling, etc.
    uint8_t readRegister(uint16_t address);
    void writeRegister(uint16_t address, uint8_t value);

private:
    SPI_HandleTypeDef *spiHandle;
    GPIO_TypeDef *csPort;
    uint16_t csPin;

    void select();
    void deselect();
    uint8_t spiTransfer(uint8_t data);
};

#endif // W5500_H
