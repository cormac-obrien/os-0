#include <stddef.h> /* for size_t */
#include <string.h>

void *memmove(void * const destination, const void * const source, const size_t num) {
    char * const dst = (char * const)destination;
    const char * const src = (const char * const)source;

    if(dst < src) {
        for(size_t i = 0; i < num; ++i) {
            dst[i] = src[i];
        }
    } else if(dst > src) {
        for(size_t i = num; i > 0; --i) {
            dst[i - 1] = src[i - 1];
        }
    }

    return destination;
}
