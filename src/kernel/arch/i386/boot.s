MB_ALIGN    equ 1<<0
MB_MEMINFO  equ 1<<1
MB_FLAGS    equ (MB_ALIGN | MB_MEMINFO)
MB_MAGIC    equ 0x1badb002
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

section .multiboot ; multiboot header
align 4
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM

section .boot_stack
stack_bottom:
times 16384 db 0 ; allocate 16 KiB for stack
stack_top:

section .text
global _start
_start:
    mov esp, stack_top

    extern kernel_early
    call kernel_early

    extern _init
    call _init

    push dword 0
    add esp, 4

    push ebx
    push eax

    extern kernel_main
    call kernel_main
    
    cli
.hang:
    hlt
    jmp .hang
