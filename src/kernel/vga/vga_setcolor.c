#include <stdint.h> /* for uint8_t */
#include <vga.h> /* for function definition and _vga_color */

void vga_setcolor(const uint8_t color) {
    _vga_color = color;
}
