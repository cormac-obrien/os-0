#include <stdlib.h>

#include <kernel.h>

uint32_t kernel_alloc_pframe(void) {
    if(_kernel_free_pages == 0) {
        abort();
    }

    const uint32_t pframe_address = *_kernel_pframe_stack_ptr;
    _kernel_pframe_stack_ptr--;
    _kernel_free_pages -= 1;

    return pframe_address;
}
