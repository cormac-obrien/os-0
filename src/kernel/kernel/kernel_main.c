#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arch.h>
#include <kernel.h>
#include <multiboot.h>

extern addr_t cpu_vendor;

void kernel_main() {
    kernel_puts((char *)&cpu_vendor);

    kernel_puts("OS-0 Pre-Alpha build booted successfully.\n\n");

    if(_kernel_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Bad magic number (got 0x%x), aborting.\n", _kernel_magic);
        return;
    }

    const mb_info_t * const mbi = (mb_info_t *)_kernel_mbi_addr;

    if((mbi->flags & MBINFO_MEMMAP) != MBINFO_MEMMAP) {
        printf("Couldn't get a memory map from the bootloader.\n");
        return;
    }
}
