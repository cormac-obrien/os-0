#include <stddef.h> /* for size_t */
#include <stdint.h> /* for uint8_t */
#include <vga.h> /* for _vga_buffer, VGA_COLRS, vga_cell() */

void vga_putcell(const char c, const uint8_t color, const size_t row, const size_t col) {
    _vga_buffer[row * VGA_COLS + col] = vga_cell(c, color);
}
