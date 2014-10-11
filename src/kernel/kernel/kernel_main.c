#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <kernel.h>
#include <multiboot.h>
#include <vga.h>

#define _4K (0x1000)
#define _1M (0x100000)
#define CKFLAG(flags, bit) ((flags) & (1 << bit))

/* for legibility, nothing else. */
typedef multiboot_info_t       mb_info_t;
typedef multiboot_memory_map_t mb_mmap_t;

extern uint32_t kernel_pframe_stack_ptr;

void kernel_main() {
    printf("OS-0 Pre-Alpha build booted successfully.\n\n");

    if(_kernel_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Bad magic number (got 0x%x), aborting.\n", _kernel_magic);
        return;
    }

    /* retrieve multiboot info from the indicated address */
    const mb_info_t * const mbi = (mb_info_t *)_kernel_mbi_addr;

    /* no point continuing if we can't get a memory map */
    if(!CKFLAG(mbi->flags, 6)) return;

    const mb_mmap_t *mmap = (mb_mmap_t *)mbi->mmap_addr;
    const uint32_t mmap_end = mbi->mmap_addr + mbi->mmap_length;

    while((uint32_t)mmap < mmap_end) {
        /* type 1 segments are the only ones available for our use */
        if(mmap->type != 1) {
            mmap = (mb_mmap_t *)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
            continue;
        }

        /* if the segment starts at 1M, it contains the kernel and we need   *
         * to skip that memory so we don't overwrite our OS.                 */
        const uint32_t offset =
            (mmap->addr == _1M) ?
                (uint32_t)(&kernel_pframe_stack_ptr) : 0;

        uint32_t first_pframe = mmap->addr + offset;
        if(first_pframe % _4K != 0) {
            first_pframe += _4K - (first_pframe % _4K);
        }

        uint32_t last_pframe = mmap->addr + mmap->len - _4K;
        if(last_pframe % _4K != 0) {
            last_pframe -= last_pframe % _4K;
        }

        const uint32_t num_pframes = (last_pframe - first_pframe) / _4K;

        printf("First pframe: %x | ", first_pframe);
        printf("Last pframe: %x | ", last_pframe);
        printf("Total pframes: %x\n\n", num_pframes);

        for(uint32_t i = 0; i < num_pframes; ++i) {
            (&kernel_pframe_stack_ptr)[i] = first_pframe + (_4K * i);
        }

        /* Move pointer to next block */
        mmap = (mb_mmap_t *)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
    }
}
