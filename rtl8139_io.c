#include "rtl8139_io.h"

void outl(uint16_t port, uint32_t value) {
    asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

uint32_t inl(uint16_t port) {
    uint32_t value;
    asm volatile ("inl %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void outb_p(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1\noutb %%al, $0x80" : : "a"(value), "Nd"(port));
}

uint8_t inb_p(uint16_t port) {
    uint8_t value;
    asm volatile ("inb %1, %0\noutb %%al, $0x80" : "=a"(value) : "Nd"(port));
    return value;
}

void outw_p(uint16_t port, uint16_t value) {
    asm volatile ("outw %0, %1\noutb %%al, $0x80" : : "a"(value), "Nd"(port));
}

uint16_t inw_p(uint16_t port) {
    uint16_t value;
    asm volatile ("inw %1, %0\noutb %%al, $0x80" : "=a"(value) : "Nd"(port));
    return value;
}

void outl_p(uint16_t port, uint32_t value) {
    asm volatile ("outl %0, %1\noutb %%al, $0x80" : : "a"(value), "Nd"(port));
}

uint32_t inl_p(uint16_t port) {
    uint32_t value;
    asm volatile ("inl %1, %0\noutb %%al, $0x80" : "=a"(value) : "Nd"(port));
    return value;
}
