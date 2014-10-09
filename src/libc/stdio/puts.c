#include <stdio.h>

#include <kernel.h>

int puts(const char * const str) {
    kernel_puts(str);

    return 0;
}
