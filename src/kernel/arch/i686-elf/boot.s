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

  extern idt_setup
  call idt_setup

  lidt [idtr]

  xchg bx,bx

  int 0x0
    
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

global gdtr
gdtr:
dw gdt.end - gdt - 1
dd gdt
dw 0

global idtr
idtr:
dw idt.end - idt - 1
dd idt
dw 0

section .gdt
global gdt
gdt:
times 256 dq 0 ; each entry is 64 bits
.end:

section .idt
global idt
idt:
times 256 dq 0 ; each entry is 64 bits
.end:
