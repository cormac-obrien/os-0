#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <kernel.h>

int printf(const char * const format, ...) {
    va_list args;
    va_start(args, format);

    int chars_written = 0;

    for(size_t i = 0; i < strlen(format); ++i) {
        if(format[i] == '%') {
            //
        } else {
            kernel_putchar(format[i]);
            chars_written += 1;
        }
    }

    va_end(args);

    return chars_written;
}
