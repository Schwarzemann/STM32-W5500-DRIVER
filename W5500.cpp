#include "W5500.h"

W5500::W5500(SPI_HandleTypeDef *hspi, GPIO_TypeDef *csPort, uint16_t csPin)
    : spiHandle(hspi), csPort(csPort), csPin(csPin) {}

bool W5500::initialize() {
    uint8_t version = readRegister(0x0039);  // Check W5500 version register
    return (version == 0x04);  // W5500 returns version 0x04
}

uint8_t W5500::readRegister(uint16_t address) {
    select();
    spiTransfer((address & 0xFF00) >> 8);  // Address high byte
    spiTransfer(address & 0x00FF);         // Address low byte
    spiTransfer(0x00);                     // Control byte (Read, Common Register)
    uint8_t value = spiTransfer(0x00);     // Read the value
    deselect();
    return value;
}

void W5500::writeRegister(uint16_t address, uint8_t value) {
    select();
    spiTransfer((address & 0xFF00) >> 8);  // Address high byte
    spiTransfer(address & 0x00FF);         // Address low byte
    spiTransfer(0x04);                     // Control byte (Write, Common Register)
    spiTransfer(value);                    // Write the value
    deselect();
}

void W5500::select() {
    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);
}

void W5500::deselect() {
    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
}

uint8_t W5500::spiTransfer(uint8_t data) {
    uint8_t receivedData;
    HAL_SPI_TransmitReceive(spiHandle, &data, &receivedData, 1, HAL_MAX_DELAY);
    return receivedData;
}
