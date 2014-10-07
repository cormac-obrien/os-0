#include <stddef.h> /* for size_t */
#include <string.h>

void *memcpy(void * const destination, const void * const source, const size_t num) {
    unsigned char * const dst = (unsigned char * const)destination;
    const unsigned char * const src = (const unsigned char * const)source;

    for(size_t i = 0; i < num; ++i) {
        dst[i] = src[i];
    }

    return destination;
}
