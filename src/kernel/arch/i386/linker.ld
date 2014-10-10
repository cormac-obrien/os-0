ENTRY(_start)

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
        kernel_end_ptr = .;
    }

    .skip BLOCK(4K) : ALIGN(4K) {
        /* pointer to first free 4K block */
        first_free_page_ptr = .;
    }
}
