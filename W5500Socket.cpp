#include "W5500Socket.h"

W5500Socket::W5500Socket(SPI_HandleTypeDef *hspi, GPIO_TypeDef *csPort, uint16_t csPin)
    : W5500(hspi, csPort, csPin) {}

bool W5500Socket::openSocket(uint8_t socketNumber) {
    writeRegister(0x4000 + socketNumber * 0x100 + 0x01, 0x01); // Open command
    return true;
}

bool W5500Socket::closeSocket(uint8_t socketNumber) {
    writeRegister(0x4000 + socketNumber * 0x100 + 0x01, 0x10); // Close command
    return true;
}

bool W5500Socket::connect(uint8_t socketNumber, uint8_t ip[4], uint16_t port) {
    for (int i = 0; i < 4; i++) {
        writeRegister(0x4000 + socketNumber * 0x100 + 0x0C + i, ip[i]); // Destination IP
    }
    writeRegister(0x4000 + socketNumber * 0x100 + 0x10, port >> 8);    // Destination port high byte
    writeRegister(0x4000 + socketNumber * 0x100 + 0x11, port & 0xFF);  // Destination port low byte
    writeRegister(0x4000 + socketNumber * 0x100 + 0x01, 0x04);         // Connect command
    return true;
}

bool W5500Socket::disconnect(uint8_t socketNumber) {
    writeRegister(0x4000 + socketNumber * 0x100 + 0x01, 0x08); // Disconnect command
    return true;
}

int W5500Socket::send(uint8_t socketNumber, const uint8_t *data, uint16_t len) {
    // Logic to send data, write to TX buffer, and update TX write pointer
    return len; // Return bytes sent
}

int W5500Socket::receive(uint8_t socketNumber, uint8_t *data, uint16_t len) {
    // Logic to read data from RX buffer, update RX read pointer
    return len; // Return bytes received
}
