#include <stddef.h> /* for size_t */
#include <string.h>

void *memset(void * const ptr, const int value, const size_t num) {
    unsigned char * const buffer = (unsigned char * const)ptr;

    for(size_t i = 0; i < num; ++i) {
        buffer[i] = (unsigned char) value;
    }

    return ptr;
}
