#include <stdlib.h>

#include <kernel.h>

uint32_t kernel_alloc_pframe(void) {
    if(_kernel_free_pages == 0) {
        abort();
    }

    pframe_address = 0;
    _kernel_free_pages -= 1;
    return pframe_address;
}
