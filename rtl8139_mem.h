#ifndef RTL8139_MEM_H
#define RTL8139_MEM_H

#include <stddef.h>
#include <stdint.h>

// Memory operations
void* memchr(const void* ptr, int value, size_t count);
void* memcpy(uint8_t *dest, const uint8_t *src, size_t count);
void* memset(uint8_t *dest, uint8_t value, size_t count);
void* memcpy32(void* dest, const void* src, size_t count);
void* memcpy64(void* dest, const void* src, size_t count);
void* memmove32(void* dest, const void* src, size_t count);
void* memmove64(void* dest, const void* src, size_t count);

#endif // RTL8139_MEM_H
