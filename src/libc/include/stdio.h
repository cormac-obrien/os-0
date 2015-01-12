#ifndef _STDIO_H
#define _STDIO_H 1

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char *format, ...);
int printint(intmax_t arg);
int puts(const char *str);

#ifdef __cplusplus
}
#endif

#endif
