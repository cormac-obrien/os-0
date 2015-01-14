/* Copyright (C) 2014 Cormac O'Brien.

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arch.h>
#include <kernel.h>
#include <multiboot.h>

extern addr_t cpu_vendor;

void kernel_main() {
    kernel_puts((char *)&cpu_vendor);

    kernel_puts("OS-0 Pre-Alpha build booted successfully.\n\n");

    if(_kernel_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Bad magic number (got 0x%x), aborting.\n", _kernel_magic);
        return;
    }

    const mb_info_t * const mbi = (mb_info_t *)_kernel_mbi_addr;

    if((mbi->flags & MBINFO_MEMMAP) != MBINFO_MEMMAP) {
        kernel_puts("Couldn't get a memory map from the bootloader.\n");
        return;
    }
}
