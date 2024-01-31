#ifndef RTL8139_IO_H
#define RTL8139_IO_H

#include <stdint.h>

// I/O operations for byte (8-bit), word (16-bit), and long (32-bit) values
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
void outw(uint16_t port, uint16_t value);
uint16_t inw(uint16_t port);
void outl(uint16_t port, uint32_t value);
uint32_t inl(uint16_t port);

// Paused I/O operations for byte, word, and long values
void outb_p(uint16_t port, uint8_t value);
uint8_t inb_p(uint16_t port);
void outw_p(uint16_t port, uint16_t value);
uint16_t inw_p(uint16_t port);
void outl_p(uint16_t port, uint32_t value);
uint32_t inl_p(uint16_t port);

#endif // RTL8139_IO_H
