#include <stddef.h> /* for size_t */
#include <string.h>

int memcmp(const void * const ptr1, const void * const ptr2, const size_t num) {
    const unsigned char * const first = (const unsigned char * const)ptr1;
    const unsigned char * const second = (const unsigned char * const)ptr2;

    for(size_t i = 0; i < num; ++i) {
        if(first[i] > second[i]) {
            return 1;
        } else if(first[i] < second[i]) {
            return -1;
        }
    }

    return 0;
}
