#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <kernel.h>
#include <multiboot.h>
#include <vga.h>

#define CKFLAG(flags, bit) ((flags) & (1 << bit))

extern uint32_t kernel_end_ptr; /* see src/kernel/arch/<arch>/linker.ld */
extern uint32_t first_free_page_ptr;

void kernel_main() {
    const uint8_t vga_green = vga_color(C_GRN, C_BLK);
    const uint8_t vga_red = vga_color(C_RED, C_BLK);
    const uint8_t vga_default = vga_color(C_LGRY, C_BLK);

    printf("OS-0 Pre-Alpha build booted successfully.\n");

    if(_kernel_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        vga_setcolor(vga_red);
        printf("Bad magic number (got 0x%x), aborting.\n", _kernel_magic);
        vga_setcolor(vga_default);
        return;
    }

    /* retrieve multiboot info from the indicated address */
    multiboot_info_t *mbi = (multiboot_info_t *)_kernel_mbi_addr;

    if(CKFLAG(mbi->flags, 6)) { /* bootloader can give us a memory map */
        vga_setcolor(vga_green);
        printf("\nMEMORY MAP\n");
        vga_setcolor(vga_default);

        printf("  Beginning search for memory blocks.\n");

        /* Poll BIOS for chunks of memory and their availability */
        const multiboot_memory_map_t *mmap;
        size_t total_ram = 0;
        for(mmap = (multiboot_memory_map_t *)mbi->mmap_addr;
                (uint32_t)mmap < mbi->mmap_addr + mbi->mmap_length;
                mmap = (multiboot_memory_map_t *)((uint32_t)mmap + mmap->size + sizeof(mmap->size))) {

            if(mmap->type == 1) {
                total_ram += mmap->len;
                printf("  Addr: 0x%x | Length: 0x%x\n", mmap->addr, mmap->len);
            }
        }

        vga_setcolor(vga_green);
            printf("\nAVAILABLE RAM (w/ kernel): ");
        vga_setcolor(vga_default);

        printf("%x MiB\n", total_ram / 0x100000);

        uint32_t kernel_end_addr = (uint32_t)&kernel_end_ptr;

        vga_setcolor(vga_green);
            printf("\nKernel location: ");
        vga_setcolor(vga_default);

        printf("0x00100000 -> 0x%x.\n", kernel_end_addr);
        printf("Kernel size: 0x%x\n", kernel_end_addr - 0x00100000);

        uint32_t first_free_page_addr = (uint32_t)&first_free_page_ptr;

        vga_setcolor(vga_green);
            printf("\nPAGES\n");
        vga_setcolor(vga_default);

        printf("First free page at 0x%x\n", first_free_page_addr);
        total_ram -= (first_free_page_addr - 0x00100000);
        printf("Free pages: 0x%x\n", total_ram / 0x1000);

    }
}
