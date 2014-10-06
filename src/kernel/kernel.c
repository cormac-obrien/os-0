#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

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

uint8_t vga_color(const vga_color_t fg, const vga_color_t bg) {
    return fg | bg << 4;
}

uint16_t vga_cell(const char c, const uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}

size_t strlen(const char * const str) {
    size_t len = 0;
    while(str[len] != '\0') {
        ++len;
    }

    return len;
}

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

void vga_setcolor(const uint8_t color) {
    _vga_color = color;
}

void vga_putcell(const char c, const uint8_t color, const size_t row, const size_t col) {
    _vga_buffer[row * VGA_COLS + col] = vga_cell(c, color);
}

void kernel_putchar(const char c) {
    vga_putcell(c, _vga_color, _vga_row, _vga_col);
    if(++_vga_col == VGA_COLS) {
        _vga_col = 0;
        if(++_vga_row == VGA_ROWS) {
            _vga_row = 0;
        }
    }
}

void kernel_puts(const char * const str) {
    for(size_t i = 0; i < strlen(str); ++i) {
        switch(str[i]) {
            case '\n':
                if(++_vga_row == VGA_ROWS) {
                    _vga_row = 0;
                }
                _vga_col = 0;
                break;
            default:
                kernel_putchar(str[i]);
        }
    }
}

void kernel_main() {
    vga_init();
    kernel_puts("Hello, world!\n");
}
