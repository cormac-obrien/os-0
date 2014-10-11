#include <kernel.h>

void kernel_free_pframe(const uint32_t pframe) {
    (&kernel_pframe_stack_ptr)[++_kernel_free_pages] = pframe;
}
