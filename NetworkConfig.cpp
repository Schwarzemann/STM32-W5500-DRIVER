#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

#include "W5500.h"

class NetworkConfig : public W5500 {
public:
    NetworkConfig(SPI_HandleTypeDef *hspi, GPIO_TypeDef *csPort, uint16_t csPin);
    void setIPAddress(uint8_t ip[4]);
    void setGatewayAddress(uint8_t gateway[4]);
    void setSubnetMask(uint8_t subnet[4]);
    void setMACAddress(uint8_t mac[6]);
};

#endif // NETWORKCONFIG_H
