#include <stdio.h>

#include <kernel.h>

#define PAGE_SIZE (0x1000)

/* defined in src/kernel/arch/<arch>/linker.ld */
extern uint32_t kernel_pframe_stack_marker;

void kernel_init_pframe_stack(const mb_info_t * const mbi) {
    _kernel_free_pages = 0;
    _kernel_pframe_stack_ptr = &kernel_pframe_stack_marker;

    const mb_mmap_t *kernel_mmap = NULL;

    const mb_mmap_t *mmap = (mb_mmap_t *)mbi->mmap_addr;
    const uint32_t mmap_end_addr = mbi->mmap_addr + mbi->mmap_length;

    while((uint32_t)mmap < mmap_end_addr) {
        if(mmap->type == 1) {
            if(mmap->addr == 0x100000) { /* This block has the kernel. */
                kernel_mmap = mmap;
            } else {

                uint32_t first_pframe = mmap->addr;
                if(mmap->addr % PAGE_SIZE != 0) {
                    first_pframe += (PAGE_SIZE - (mmap->addr % PAGE_SIZE));
                }

                const uint32_t last_pframe = mmap->addr + mmap->len -
                        ((mmap->addr + mmap->len) % PAGE_SIZE + PAGE_SIZE);

                for(uint32_t next_pframe = first_pframe;
                    next_pframe <= last_pframe;
                    next_pframe += PAGE_SIZE
                ) {
                    *_kernel_pframe_stack_ptr = next_pframe;
                    _kernel_pframe_stack_ptr++;
                    _kernel_free_pages += 1;
                }
            }
        }
        /* move pointer to next map block */
        mmap = (mb_mmap_t *)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
    }

    if(kernel_mmap != NULL) {
        mmap = kernel_mmap;
        const uint32_t last_pframe = mmap->addr + mmap->len -
                ((mmap->addr + mmap->len) % PAGE_SIZE + PAGE_SIZE);

        for(uint32_t next_pframe = last_pframe;
            next_pframe >= (uint32_t)_kernel_pframe_stack_ptr + 100 * PAGE_SIZE;
            next_pframe -= PAGE_SIZE
        ) {
            *_kernel_pframe_stack_ptr = next_pframe;
            _kernel_pframe_stack_ptr++;
            _kernel_free_pages += 1;
        }
    }

    printf("Allocated 0x%x page frames.\n", _kernel_free_pages);

    _kernel_pframe_stack_ptr = &kernel_pframe_stack_marker;
}

#undef PAGE_SIZE
