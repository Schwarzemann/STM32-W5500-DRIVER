#ifndef RTL8139_IO_H
#define RTL8139_IO_H

#include <stdint.h>

// I/O operations
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
void outw(uint16_t port, uint16_t value);
uint16_t inw(uint16_t port);

#endif // RTL8139_IO_H
