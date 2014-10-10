#include <kernel.h>
#include <vga.h>

void kernel_putchar(const char c) {
    switch(c) {
        case '\t':
            _vga_col += 8;
            break;
        case '\r': /* FALLTHROUGH */
        case '\n':
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
