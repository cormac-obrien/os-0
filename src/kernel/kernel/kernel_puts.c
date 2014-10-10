#include <stddef.h>
#include <string.h>

#include <kernel.h>

void kernel_puts(const char * const str) {
    for(size_t i = 0; i < strlen(str); ++i) {
        kernel_putchar(str[i]);
    }
}
