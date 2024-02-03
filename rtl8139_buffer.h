#ifndef RTL8139_BUFFER_H
#define RTL8139_BUFFER_H

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h> // For size_t

// Definition of the Buffer structure
typedef struct {
    uint8_t *data; // Pointer to the buffer's data
    size_t size;   // Size of the buffer
} Buffer;

// Function declarations
Buffer create_buffer(size_t size);                // Creates a new buffer of the specified size
void destroy_buffer(Buffer *buffer);              // Frees the buffer's memory and resets its size

Buffer clone_buffer(const Buffer *src);           // Creates a copy of the given buffer
void resize_buffer(Buffer *buffer, size_t new_size); // Resizes the buffer to the new specified size
void append_to_buffer(Buffer *buffer, const uint8_t *data, size_t length); // Appends data to the buffer
void clear_buffer(Buffer *buffer);                // Clears the buffer's data and resets its size

#endif // RTL8139_BUFFER_H
