#ifndef _KERNEL_H
#define _KERNEL_H

#include <stddef.h> /* for size_t */
#include <stdint.h> /* for uint32_t */

#ifdef __cplusplus
extern "C" {
#endif

size_t _kernel_free_pages;

uint32_t _kernel_magic;
uint32_t _kernel_mbi_addr;

uint32_t kernel_alloc_pframe();
void     kernel_free_pframe(const uint32_t pframe);

void     kernel_early(const uint32_t magic, const uint32_t addr);
void     kernel_main(void);
void     kernel_putchar(const char c);
void     kernel_puts(const char * const str);


#ifdef __cplusplus
}
#endif

#endif
