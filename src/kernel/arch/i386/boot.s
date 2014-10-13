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
times 0x4000 db 0 ; allocate 16 KiB for stack
stack_top:

section .text

global _start
extern kernel_early
extern _init
extern kernel_main
_start:
    mov esp, stack_top

    push ebx ; address of mb_info_t
    push eax ; magic number (0x2badb002)

    call kernel_early
    call _init

    ; check for cpuid availability
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    xor eax, ecx
    jz .hang

    ; check for extended cpuid functionality
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .hang

    ; check for long mode support
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .hang

    call   kernel_main
    
    cli
.hang:
    hlt
    jmp .hang

check_a20:
    pushf
    push ds
    push es
    push di
    push si

    cli

    xor ax, ax
    mov es, ax
    mov di, 0x0500

    mov ax, 0xffff
    mov ds, ax
    mov si, 0x510

    mov al, byte [es:di]
    push eax

    mov al, byte [ds:si]
    push eax

    mov byte [es:di], 0x00
    mov byte [ds:si], 0xff

    cmp byte [es:di], 0xff

    pop eax
    mov byte [ds:si], al

    pop eax
    mov byte [es:di], al

    mov ax, 0
    je check_a20_finish

    mov ax, 1

check_a20_finish:
    pop si
    pop di
    pop es
    pop ds
    popf
    ret
