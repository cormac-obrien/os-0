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

#include <string.h>

#include <kernel.h>
#include <vga.h>

void kernel_putchar(const char c) {
    switch(c) {
        case '\t':
            _vga_col += 8;
            break;
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
        memmove(_vga_buffer + VGA_COLS,
                _vga_buffer,
                2 * VGA_ROWS * 2 * VGA_COLS - 2 * VGA_COLS);
        memset(_vga_buffer + VGA_COLS * (VGA_ROWS - 1),
                0,
                VGA_COLS * 2);
        _vga_row = 0;
    }
}
