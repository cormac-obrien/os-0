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

static const size_t VGA_COLS = 80;
static const size_t VGA_ROWS = 25;

size_t _vga_row;
size_t _vga_col;
uint8_t _vga_color;
uint16_t *_vga_buffer;

uint8_t vga_color(const vga_color_t fg, const vga_color_t bg);
uint16_t vga_cell(const char c, const uint8_t color);
void vga_init();
void vga_setcolor(const uint8_t color);
void vga_putcell(const char c, const uint8_t color, const size_t row, const size_t col);

#endif
