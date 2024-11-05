#ifndef W5500SOCKET_H
#define W5500SOCKET_H

#include "W5500.h"

class W5500Socket : public W5500 {
public:
    W5500Socket(SPI_HandleTypeDef *hspi, GPIO_TypeDef *csPort, uint16_t csPin);
    bool openSocket(uint8_t socketNumber);
    bool closeSocket(uint8_t socketNumber);
    bool connect(uint8_t socketNumber, uint8_t ip[4], uint16_t port);
    bool disconnect(uint8_t socketNumber);
    
    int send(uint8_t socketNumber, const uint8_t *data, uint16_t len);
    int receive(uint8_t socketNumber, uint8_t *data, uint16_t len);
};

#endif // W5500SOCKET_H
