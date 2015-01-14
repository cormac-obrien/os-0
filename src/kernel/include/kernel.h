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

#ifndef _KERNEL_H
#define _KERNEL_H

#include <stddef.h> /* for size_t */
#include <stdint.h> /* for uint32_t */
#include <multiboot.h>

#ifdef __cplusplus
extern "C" {
#endif

/* for legibility, nothing else. */
typedef multiboot_info_t       mb_info_t;
typedef multiboot_memory_map_t mb_mmap_t;

size_t _kernel_free_pages;

uint32_t  _kernel_magic;
uint32_t  _kernel_mbi_addr;
uint32_t *_kernel_page_directory;
uint32_t *_kernel_pframe_stack_ptr;

uint32_t kernel_alloc_pframe();
void     kernel_free_pframe(const uint32_t pframe);

void     kernel_early(const uint32_t magic, const uint32_t addr);
void     kernel_enable_paging();
void     kernel_init_pframe_stack(const mb_info_t * const mbi);
void     kernel_main(void);
void     kernel_putchar(const char c);
void     kernel_puts(const char * const str);


#ifdef __cplusplus
}
#endif

#endif
