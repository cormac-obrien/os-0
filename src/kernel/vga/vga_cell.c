#include <vga.h>

uint16_t vga_cell(const char c, const uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}
