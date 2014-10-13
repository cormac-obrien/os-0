#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <kernel.h>
#include <multiboot.h>

#define _4K (0x1000)
#define _1M (0x100000)
#define CKFLAG(flags, bit) ((flags) & (1 << bit))

void kernel_main() {
    printf("OS-0 Pre-Alpha build booted successfully.\n\n");

    if(_kernel_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Bad magic number (got 0x%x), aborting.\n", _kernel_magic);
        return;
    }

    printf("Magic number verified.\n");

    /* retrieve multiboot info from the indicated address */
    const mb_info_t * const mbi = (mb_info_t *)_kernel_mbi_addr;

    if(!CKFLAG(mbi->flags, 6)) return; /* gotta get that mmap */

    kernel_init_pframe_stack(mbi);

    const uint32_t page_directory_addr = kernel_alloc_pframe();
    printf("Page directory at 0x%x.\n", page_directory_addr);
    _kernel_page_directory = (uint32_t *)page_directory_addr;
    for(size_t i = 0; i < 1024; ++i) {
        _kernel_page_directory[i] = 0 | 2;
    }

    const uint32_t page_table_addr = kernel_alloc_pframe();
    printf("First page table at 0x%x.\n", page_table_addr);
    uint32_t * const page_table = (uint32_t *)page_table_addr;
    uint32_t address = 0;
    for(size_t i = 0; i < 1024; ++i) {
        page_table[i] = address | 3;
        address += 0x1000;
    }

    _kernel_page_directory[0] = (uint32_t)page_table;
    _kernel_page_directory[0] |= 3;

    kernel_enable_paging();

}
