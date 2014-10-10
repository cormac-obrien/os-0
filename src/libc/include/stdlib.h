#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <stddef.h> /* for size_t */
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXIT_FAILURE (1)
#define EXIT_SUCCESS (0)
#define NULL ((void *)0)

void abort(void);

void *malloc(const size_t size);
void *calloc(const size_t num, const size_t size);
void *realloc(void *ptr, const size_t size);

void free(void *ptr);

#ifdef __cplusplus
}
#endif

#endif
