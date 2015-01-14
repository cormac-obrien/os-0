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

#ifndef _VGA_H
#define _VGA_H

#include <stddef.h> /* for size_t */
#include <stdint.h> /* for uint8_t, uin16_t */

typedef enum vga_color_t {
    C_BLK  =  0, C_BLU  =  1, C_GRN  =  2, C_CYN  =  3,
    C_RED  =  4, C_PNK  =  5, C_BRN  =  6, C_LGRY =  7,
    C_DGRY =  8, C_LBLU =  9, C_LGRN = 10, C_LCYN = 11,
    C_LRED = 12, C_LPNK = 13, C_LBRN = 14, C_WHT  = 15
} vga_color_t;

static const size_t  VGA_COLS = 80;
static const size_t  VGA_ROWS = 25;

size_t _vga_row;
size_t _vga_col;
uint8_t _vga_color;
static uint16_t * const _vga_buffer = (uint16_t *)0xb8000;

uint8_t vga_color(
        const vga_color_t fg,
        const vga_color_t bg);

uint16_t vga_cell(
        const char    c,
        const uint8_t color);

void vga_init();

void vga_setcolor(
        const uint8_t color);

void vga_putcell(
        const char    c,
        const uint8_t color,
        const size_t  row,
        const size_t  col);

#endif
