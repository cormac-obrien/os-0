MB_ALIGN    equ 1<<0
MB_MEMINFO  equ 1<<1
MB_FLAGS    equ MB_ALIGN | MB_MEMINFO
MB_MAGIC    equ 0x1badb002
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

section .multiboot
align 4
dd MB_MAGIC
dd MB_FLAGS
dd MB_CHECKSUM

section .boot_stack
stack_bottom:
times 0x4000 db 0
stack_top:

section .text
global _start
_start:
    xchg bx,bx
    mov esp,stack_top

    push ebx ; multiboot info struct
    push eax ; magic number

    extern kernel_early
    call   kernel_early

    xor eax,eax ; get vendor string
    cpuid
    mov [cpu_vendor+0],ebx
    mov [cpu_vendor+4],edx
    mov [cpu_vendor+8],ecx

    mov eax,1 ; get features
    cpuid
    mov [cpu_features],edx

    extern _init
    call   _init

    extern kernel_main
    call   kernel_main
    
    cli
.hang:
    hlt
    jmp .hang

section .data

global cpu_vendor
cpu_vendor:
db "VendorString", 0x0a, 0x00
cpu_features:
resd 1

global idt
idt:

global gdt
gdt:
.null: ; null descriptor is unused, so we store a pointer to the gdt here
    dw gdt.end - gdt - 1
    dd gdt
    dw 0
.kcode:
    times 2 dd 0
    times 4 db 0
.kdata:
    times 2 dd 0
    times 4 db 0
.tss:
    times 2 dd 0
    times 4 db 0
.end:

resb 65536 - 1 - (gdt.end - gdt)
