#include <kernel.h>

void kernel_free_pframe(const uint32_t pframe) {
    _kernel_pframe_stack_ptr--;
    *_kernel_frame_stack_ptr = pframe;
    _kernel_free_pages += 1;
}
