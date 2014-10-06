#include <stddef.h>
#include <string.h>

size_t strlen(const char * const str) {
    size_t len = 0;
    while(str[len] != '\0') {
        len += 1;
    }

    return len;
}
