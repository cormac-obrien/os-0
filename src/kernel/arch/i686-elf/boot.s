 ; Copyright (C) 2014 Cormac O'Brien.

 ; Permission is hereby granted, free of charge, to any person obtaining a copy
 ; of this software and associated documentation files (the "Software"), to
 ; deal in the Software without restriction, including without limitation the
 ; rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 ; sell copies of the Software, and to permit persons to whom the Software is
 ; furnished to do so, subject to the following conditions:

 ; The above copyright notice and this permission notice shall be included in
 ; all copies or substantial portions of the Software.

 ; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 ; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 ; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 ; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 ; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 ; FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 ; IN THE SOFTWARE.

MB_MAGIC equ 0x1badb002
MB_FLAGS equ 11b ; align and meminfo
MB_CHECK equ -(MB_MAGIC + MB_FLAGS)

section .multiboot
align 4
dd MB_MAGIC
dd MB_FLAGS
dd MB_CHECK

section .boot_stack
stack_bottom:
times 0x4000 db 0
stack_top:

section .text
global _start
_start:
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

global cpu_features
cpu_features:
dd 0x00000000

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
