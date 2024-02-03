#include "buffer.h"
#include "memory.h"

// Clones an existing buffer, creating a new buffer with the same data.
Buffer clone_buffer(const Buffer *src) {
    // Create a new buffer with the same size as the source buffer.
    Buffer newBuffer = create_buffer(src->size);
    // Copy data from the source buffer to the new buffer.
    memcpy(newBuffer.data, src->data, src->size);
    return newBuffer;
}

// Resizes an existing buffer to a new size.
void resize_buffer(Buffer *buffer, size_t new_size) {
    // Attempt to reallocate the buffer's data array to the new size.
    buffer->data = realloc(buffer->data, new_size);
    if (buffer->data != NULL) { // If reallocation is successful,
        buffer->size = new_size; // update the buffer size.
    }
    // Note: Reallocation failure handling could involve setting an error flag,
    // returning an error code, or other application-specific error handling.
}

// Appends data to the end of an existing buffer.
void append_to_buffer(Buffer *buffer, const uint8_t *data, size_t length) {
    // Calculate new size of the buffer after appending the data.
    size_t new_size = buffer->size + length;
    // Attempt to reallocate the buffer to accommodate the new data.
    buffer->data = realloc(buffer->data, new_size);
    if (buffer->data != NULL) { // If reallocation is successful,
        // Copy the new data to the end of the buffer.
        memcpy(buffer->data + buffer->size, data, length);
        // Update the buffer size.
        buffer->size = new_size;
    }
    // Note: Reallocation failure handling is not explicitly done here but is important.
}

// Clears the data from a buffer and resets its size to 0.
void clear_buffer(Buffer *buffer) {
    // Free the buffer's data.
    free(buffer->data);
    // Set the data pointer to NULL to indicate it's no longer pointing to valid data.
    buffer->data = NULL;
    // Reset the buffer's size to 0.
    buffer->size = 0;
}
