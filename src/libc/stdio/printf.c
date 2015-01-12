#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h> /* for size_t */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <kernel.h>

inline bool isflag(const char c) {
    return c == '-' || c == '+' || c == ' ' || c == '#' || c == '0';
}

int printf(const char * const format, ...) {
    va_list args;
    va_start(args, format);

    int chars_written = 0;

    const size_t fmt_len = strlen(format);

    for(size_t i = 0; i < strlen(format); ++i) {
        if(format[i] == '%') {
            if(++i < fmt_len)
                return -1;

            if(format[i] == '%') {
                kernel_putchar('%');

            } else if(format[i] == 'c') {
                kernel_putchar((char)va_arg(args, int));

            } else if(format[i] == 's') {
                puts(va_arg(args, const char * const));

            } else if(format[i] == 'x') {
                // bool leading = true;
                const uint64_t x = va_arg(args, uint64_t);
                const char * const hex = "0123456789abcdef";

                for(size_t i = 8; i > 0; --i) {
                    const char c = hex[(x >> ((i - 1) * 4)) & 0xf];
                    kernel_putchar(c);
                }
            
            } else {
                abort();
            }
        } else {
            kernel_putchar(format[i]);
            chars_written += 1;
        }
    }

    va_end(args);

    return chars_written;
}
