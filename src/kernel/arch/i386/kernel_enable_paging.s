extern _kernel_page_directory
global kernel_enable_paging
section .text
kernel_enable_paging:
    mov eax, [_kernel_page_directory]
    mov cr3, eax

    mov eax, cr0
    or  eax, 0x80000000
    mov cr0, eax
    ret
