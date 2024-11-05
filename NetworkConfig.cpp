#include "NetworkConfig.h"

NetworkConfig::NetworkConfig(SPI_HandleTypeDef *hspi, GPIO_TypeDef *csPort, uint16_t csPin)
    : W5500(hspi, csPort, csPin) {}

void NetworkConfig::setIPAddress(uint8_t ip[4]) {
    writeRegister(0x000F, ip[0]);
    writeRegister(0x0010, ip[1]);
    writeRegister(0x0011, ip[2]);
    writeRegister(0x0012, ip[3]);
}

void NetworkConfig::setGatewayAddress(uint8_t gateway[4]) {
    writeRegister(0x0001, gateway[0]);
    writeRegister(0x0002, gateway[1]);
    writeRegister(0x0003, gateway[2]);
    writeRegister(0x0004, gateway[3]);
}

void NetworkConfig::setSubnetMask(uint8_t subnet[4]) {
    writeRegister(0x0005, subnet[0]);
    writeRegister(0x0006, subnet[1]);
    writeRegister(0x0007, subnet[2]);
    writeRegister(0x0008, subnet[3]);
}

void NetworkConfig::setMACAddress(uint8_t mac[6]) {
    writeRegister(0x0009, mac[0]);
    writeRegister(0x000A, mac[1]);
    writeRegister(0x000B, mac[2]);
    writeRegister(0x000C, mac[3]);
    writeRegister(0x000D, mac[4]);
    writeRegister(0x000E, mac[5]);
}
