#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <kernel.h>

int printf(const char * const format, ...) {
    va_list args;
    va_start(args, format);

    int chars_written = 0;

    const size_t fmt_len = strlen(format);

    for(size_t i = 0; i < strlen(format); ++i) {
        if(format[i] == '%') {
            if(++i < fmt_len) {

                if(format[i] == '%') {
                    kernel_putchar('%');

                } else if(format[i] == 'c') {
                    kernel_putchar((char)va_arg(args, int));

                } else if(format[i] == 's') {
                    kernel_puts(va_arg(args, const char * const));

                } else {
                    abort();
                }
            } else { 
                return -1;
            }
        } else {
            kernel_putchar(format[i]);
            chars_written += 1;
        }
    }

    va_end(args);

    return chars_written;
}
