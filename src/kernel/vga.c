/* Copyright (C) 2014 Cormac O'Brien.

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

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
