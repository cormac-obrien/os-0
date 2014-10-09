do_e820:
    xor ebx, ebx              ; clear ebx
    xor bp,  bp
    mov edx, 0x0534d4150
    mov eax, 0xe820
    mov [es:di + 20], dword 1
    mov ecx, 24
    int 0x15
    jc short .failed
    mov edx, 0x0534d4150
    cmp eax, edx
    jne short .failed
    test ebx, ebx
    je short .failed
    jmp short .jmpin
.e820lp:
    mov eax, 0xe820
    mov [es:di + 20], dword 1
    mov ecx, 24
    int 0x15
    jc short .e820f
    mov edx, 0x0534d4150
.jmpin:
    jcxz .skipent
    cmp cl, 20
    jbe short .notext
    test byte [es:di + 20], 1
    je short .skipent
.notext:
    mov ecx, [es:di + 8]
    or ecx, [es:di + 12]
    jz .skipent
    inc bp
    add di, 24
.e820f:
    mov [mmap_ent], bp
    clc
    ret
.failed:
    stc
    ret
