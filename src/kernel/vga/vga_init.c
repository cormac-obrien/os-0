#include <vga.h>

void vga_init() {
    _vga_row = 0;
    _vga_col = 0;
    _vga_color = vga_color(C_LGRY, C_BLK);
    _vga_buffer = (uint16_t *)0xb8000;

    uint16_t blank_cell = vga_cell(' ', _vga_color);

    for(size_t row = 0; row < VGA_ROWS; ++row) {
        for(size_t col = 0; col < VGA_COLS; ++col) {
            _vga_buffer[row * VGA_COLS + col] = blank_cell;
        }
    }
}
