#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#include <stddef.h> /* for size_t */

size_t strlen(const char * const str);
int memcmp(const void * const ptr1, const void * const ptr2, const size_t num);
void *memcpy(void * const destination, const void * const source, const size_t num);
void *memmove(void * const destination, const void * const source, const size_t num);
void *memset(void * const ptr, const int value, const size_t num);

#endif
