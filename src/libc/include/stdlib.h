#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXIT_FAILURE (-1)
#define EXIT_SUCCESS (0)
#define NULL ((void *)0)

void abort(void);

#ifdef __cplusplus
}
#endif

#endif
