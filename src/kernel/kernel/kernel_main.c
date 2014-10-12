#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
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
}
