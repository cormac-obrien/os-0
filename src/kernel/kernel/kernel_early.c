#include <kernel.h>
#include <vga.h>

void kernel_early(uint32_t magic, uint32_t addr) {
    _kernel_magic = magic;
    _kernel_mbi_addr = addr;
    vga_init();
}
