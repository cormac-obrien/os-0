#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <vga.h>

size_t strlen(const char * const str) {
    size_t len = 0;
    while(str[len] != '\0') {
        ++len;
    }

    return len;
}

void kernel_putchar(const char c) {
    switch(c) {
        case '\n':
            _vga_row += 1;
            _vga_col = 0;
            break;
        default:
            vga_putcell(c, _vga_color, _vga_row, _vga_col);
            _vga_col += 1;
            break;
    }

    if(_vga_col == VGA_COLS) {
        _vga_col = 0;
        _vga_row += 1;
    }

    if(_vga_row == VGA_ROWS) {
        _vga_row = 0;
    }
}

void kernel_puts(const char * const str) {
    for(size_t i = 0; i < strlen(str); ++i) {
        kernel_putchar(str[i]);
    }
}

void kernel_early() {
    vga_init();
}

void kernel_main() {
    kernel_puts("OS-0 Pre-Alpha build.\n");
    kernel_puts("System booted successfully.");
}
