ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS {
    . = 1M; /* 1 MiB offset */

    /* multiboot goes first, followed by .text */
    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMON)
        *(.bss)
        *(.boot_stack)
        kernel_pframe_stack_marker = .;
    }
}
