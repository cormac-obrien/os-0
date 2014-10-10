#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <multiboot.h>
#include <vga.h>

#define CKFLAG(flags, bit) ((flags) & (1 << bit))

extern uint32_t end_kernel; /* see src/kernel/arch/<arch>/linker.ld */

void kernel_putchar(const char c) {
    switch(c) {
        case '\t':
            _vga_col += 8;
            break;
        case '\r': /* FALLTHROUGH */
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
        printf("Failed (got 0x%x)", _kernel_magic);
        return;
    }

    multiboot_info_t *mbi = (multiboot_info_t *)_kernel_mbi_addr;

    vga_setcolor(vga_color(C_GRN, C_BLK));
    printf("OK\n");
    vga_setcolor(vga_color(C_LGRY, C_BLK));

    if(CKFLAG(mbi->flags, 6)) {
        vga_setcolor(vga_color(C_GRN, C_BLK));
        printf("\nMEMORY MAP\n");
        vga_setcolor(vga_color(C_LGRY, C_BLK));

        printf("  Beginning search for memory blocks.\n");

        typedef multiboot_memory_map_t memmap_t;

        /* It looks worse than it is, I swear */
        const memmap_t *mmap;
        for(mmap = (memmap_t *)mbi->mmap_addr;
                (uint32_t)mmap < mbi->mmap_addr + mbi->mmap_length;
                mmap = (memmap_t *)((uint32_t)mmap + mmap->size + sizeof(mmap->size))) {

            /* TODO: massive kludge right here */
            printf("  Address: 0x%x | Length: 0x%x | Type: 0x%x\n",
                    mmap->addr & 0xffffffff,
                    mmap->len,
                    mmap->type);
        }
    }
}
