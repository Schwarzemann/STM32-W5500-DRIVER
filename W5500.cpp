#include "W5500.h"

// Constructor
W5500::W5500(SPI_HandleTypeDef *hspi, GPIO_TypeDef *csPort, uint16_t csPin)
    : spiHandle(hspi), csPort(csPort), csPin(csPin) {}

// Initialize W5500
bool W5500::initialize() {
    uint8_t version = readRegister(0x0039);  // Common register for version check
    return (version == 0x04);  // W5500 should return version 0x04
}

// Set IP Address
void W5500::setIPAddress(uint8_t ip[4]) {
    writeRegister(0x000F, ip[0]); // SIPR Register start address
    writeRegister(0x0010, ip[1]);
    writeRegister(0x0011, ip[2]);
    writeRegister(0x0012, ip[3]);
}

// Set Gateway Address
void W5500::setGatewayAddress(uint8_t gateway[4]) {
    writeRegister(0x0001, gateway[0]);  // GAR Register start address
    writeRegister(0x0002, gateway[1]);
    writeRegister(0x0003, gateway[2]);
    writeRegister(0x0004, gateway[3]);
}

// Set Subnet Mask
void W5500::setSubnetMask(uint8_t subnet[4]) {
    writeRegister(0x0005, subnet[0]);  // SUBR Register start address
    writeRegister(0x0006, subnet[1]);
    writeRegister(0x0007, subnet[2]);
    writeRegister(0x0008, subnet[3]);
}

// Set MAC Address
void W5500::setMACAddress(uint8_t mac[6]) {
    writeRegister(0x0009, mac[0]); // SHAR Register start address
    writeRegister(0x000A, mac[1]);
    writeRegister(0x000B, mac[2]);
    writeRegister(0x000C, mac[3]);
    writeRegister(0x000D, mac[4]);
    writeRegister(0x000E, mac[5]);
}

// Read Register
uint8_t W5500::readRegister(uint16_t address) {
    select();
    spiTransfer((address & 0xFF00) >> 8);  // Address high byte
    spiTransfer(address & 0x00FF);         // Address low byte
    spiTransfer(0x00);                     // Control byte (Read, Common Register)
    uint8_t value = spiTransfer(0x00);     // Read the value
    deselect();
    return value;
}

// Write Register
void W5500::writeRegister(uint16_t address, uint8_t value) {
    select();
    spiTransfer((address & 0xFF00) >> 8);  // Address high byte
    spiTransfer(address & 0x00FF);         // Address low byte
    spiTransfer(0x04);                     // Control byte (Write, Common Register)
    spiTransfer(value);                    // Write the value
    deselect();
}

// Select W5500 (CS Low)
void W5500::select() {
    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);
}

// Deselect W5500 (CS High)
void W5500::deselect() {
    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
}

// SPI Transfer
uint8_t W5500::spiTransfer(uint8_t data) {
    uint8_t receivedData;
    HAL_SPI_TransmitReceive(spiHandle, &data, &receivedData, 1, HAL_MAX_DELAY);
    return receivedData;
}
