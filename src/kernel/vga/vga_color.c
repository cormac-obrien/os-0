#include <vga.h>

uint8_t vga_color(const vga_color_t fg, const vga_color_t bg) {
    return fg | bg << 4;
}
