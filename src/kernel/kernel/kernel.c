#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <multiboot.h>
#include <vga.h>

#define CKFLAG(flags, bit) ((flags) & (1 << bit))

void kernel_putchar(const char c) {
    switch(c) {
        case '\t':
            _vga_col += 8;
            break;
        case '\n':
        case '\r': /* FALLTHROUGH */
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
        _vga_row = 0;
    }
}

void kernel_puts(const char * const str) {
    for(size_t i = 0; i < strlen(str); ++i) {
        kernel_putchar(str[i]);
    }
}

static uint32_t _kernel_magic;
static uint32_t _kernel_mbi_addr;
void kernel_early(uint32_t magic, uint32_t addr) {
    _kernel_magic = magic;
    _kernel_mbi_addr = addr;
    vga_init();
}

void kernel_main() {
    printf("OS-0 Pre-Alpha build booted successfully.\n");
    printf("Checking magic number...");

    if(_kernel_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Failed (got %x)", _kernel_magic);
        return;
    }

    vga_setcolor(vga_color(C_GRN, C_BLK));
    printf("OK\n");
    vga_setcolor(vga_color(C_LGRY, C_BLK));

    multiboot_info_t *mbi = (multiboot_info_t *)_kernel_mbi_addr;
    printf("Flags = %x\n", mbi->flags);

    if(CKFLAG(mbi->flags, 0)) {
        vga_setcolor(vga_color(C_GRN, C_BLK));
        printf("\nMEMORY\n");
        vga_setcolor(vga_color(C_LGRY, C_BLK));
        printf("  Available lower memory = %x KiB\n", mbi->mem_lower);
        printf("  Available upper memory = %x KiB\n", mbi->mem_upper);
    } else {
        vga_setcolor(vga_color(C_RED, C_BLK));
        printf("\nFailed to get memory stats.\n");
        vga_setcolor(vga_color(C_LGRY, C_BLK));
    }

    if(CKFLAG(mbi->flags, 1)) {
        vga_setcolor(vga_color(C_GRN, C_BLK));
        printf("\nBOOT DEVICE\n");
        vga_setcolor(vga_color(C_LGRY, C_BLK));
        printf("  Got ID %x.\n", mbi->boot_device);
    }
}
