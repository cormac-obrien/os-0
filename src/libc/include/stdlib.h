#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <stddef.h> /* for size_t */
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXIT_FAILURE (-1)
#define EXIT_SUCCESS (0)
#define NULL ((void *)0)

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

typedef struct {
    long long quot;
    long long rem;
} lldiv_t;

void abort(void);
double atof(const char * const str);
int atoi(const char * const str);
long atol(const char * const str);
long long atoll(const char * const str);
double strtod(const char * const str, char **endptr);
float strtof(const char * const str, char **endptr);
long strtol(const char * const str, char **endptr, const int base);
long double strtold(const char * const str, const char **endptr);
long long strtoll(const char * const str, char **endptr, const int base);
unsigned long strtoul(const char * const str, char **endptr, const int base);
unsigned long long strtoull(const char * const str, char **endptr, const int base);

#ifdef __cplusplus
}
#endif

#endif
