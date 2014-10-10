#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t _kernel_magic;
uint32_t _kernel_mbi_addr;

void kernel_early(const uint32_t magic, const uint32_t addr);
void kernel_main(void);
void kernel_putchar(const char c);
void kernel_puts(const char * const str);

#ifdef __cplusplus
}
#endif

#endif
