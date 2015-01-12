#include <vga.h>

#include <stddef.h>
#include <stdint.h>

inline uint16_t
vga_cell(
        const char c,
        const uint8_t color
) {
    return (uint16_t)c | (uint16_t)color << 8;
}

inline uint8_t vga_color(
        const vga_color_t fg,
        const vga_color_t bg
) {
    return fg | bg << 4;
}

void vga_init()
{
    _vga_row = 0;
    _vga_col = 0;
    _vga_color = vga_color(C_LGRY, C_BLK);

    uint16_t blank_cell = vga_cell(' ', _vga_color);

    for(size_t row = 0; row < VGA_ROWS; ++row) {
        for(size_t col = 0; col < VGA_COLS; ++col) {
            _vga_buffer[row * VGA_COLS + col] = blank_cell;
        }
    }
}

inline void
vga_putcell(
        const char    c,
        const uint8_t color,
        const size_t  row,
        const size_t  col
) {
    _vga_buffer[row * VGA_COLS + col] = vga_cell(c, color);
}

void
vga_setcolor(
        const uint8_t color
) {
    _vga_color = color;
}
