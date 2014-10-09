#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <multiboot.h>
#include <vga.h>

void kernel_putchar(const char c) {
    switch(c) {
        case '\t':
            _vga_col += 8;
            break;
        case '\n':
        case '\r': /* FALLTHROUGH */
            _vga_row += 1;
            _vga_col = 0;
            break;
        default:
            vga_putcell(c, _vga_color, _vga_row, _vga_col);
            _vga_col += 1;
            break;
    }

    if(_vga_col >= VGA_COLS) {
        _vga_col = 0;
        _vga_row += 1;
    }

    if(_vga_row >= VGA_ROWS) {
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

void kernel_main(struct multiboot_info *mbd, unsigned int magic) {
    kernel_puts("OS-0 Pre-Alpha build booted successfully.\n");

    kernel_puts("Checking for 4K page boundary alignment...");
    if(mbd->flags & ((uint32_t)1 << 1)) {
        kernel_puts("Ok.\n");
    } else {
        kernel_puts("Failed.\n");
    }

    kernel_puts("Getting size of lower memory...");
}
