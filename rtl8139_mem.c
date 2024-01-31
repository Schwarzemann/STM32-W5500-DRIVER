#include "rtl8139_mem.h"

// Searches the first 'count' bytes of the block of memory pointed by 'ptr' 
// for the first occurrence of 'value' (interpreted as an unsigned char) and 
// returns a pointer to it.
void* memchr(const void* ptr, int value, size_t count) {
    const uint8_t* p = (const uint8_t*)ptr;
    while (count--) {
        if (*p == (uint8_t)value) {
            return (void*)p;
        }
        p++;
    }
    return NULL;
}

// Copies 'count' elements, each of size 32-bit (4 bytes), from 'src' to 'dest'.
// Returns a pointer to 'dest'.
void* memcpy32(void* dest, const void* src, size_t count) {
    uint32_t* d = (uint32_t*)dest;
    const uint32_t* s = (const uint32_t*)src;
    while (count--) {
        *d++ = *s++;
    }
    return dest;
}

// Copies 'count' elements, each of size 64-bit (8 bytes), from 'src' to 'dest'.
// Returns a pointer to 'dest'.
void* memcpy64(void* dest, const void* src, size_t count) {
    uint64_t* d = (uint64_t*)dest;
    const uint64_t* s = (const uint64_t*)src;
    while (count--) {
        *d++ = *s++;
    }
    return dest;
}

// Moves 'count' elements, each of size 32-bit, from 'src' to 'dest', handling 
// overlapping source and destination memory blocks.
// Returns a pointer to 'dest'.
void* memmove32(void* dest, const void* src, size_t count) {
    if (dest < src) {
        memcpy32(dest, src, count);
    } else {
        uint32_t* d = (uint32_t*)dest + count - 1;
        const uint32_t* s = (const uint32_t*)src + count - 1;
        while (count--) {
            *d-- = *s--;
        }
    }
    return dest;
}

// Moves 'count' elements, each of size 64-bit, from 'src' to 'dest', handling 
// overlapping source and destination memory blocks.
// Returns a pointer to 'dest'.
void* memmove64(void* dest, const void* src, size_t count) {
    if (dest < src) {
        memcpy64(dest, src, count);
    } else {
        uint64_t* d = (uint64_t*)dest + count - 1;
        const uint64_t* s = (const uint64_t*)src + count - 1;
        while (count--) {
            *d-- = *s--;
        }
    }
    return dest;
}
