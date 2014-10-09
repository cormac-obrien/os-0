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

void abort(void);

/* _____________________________________________________________________ ABS */
      int   abs(const      int  n);
     long  labs(const      long n);
long long llabs(const long long n);

void *malloc(const size_t size);
void *calloc(const size_t num, const size_t size);
void *realloc(void *ptr, const size_t size);

void free(void *ptr);

/* _____________________________________________________________________ DIV */
typedef struct {       int quot;      int  rem; }   div_t;
typedef struct {      long quot;      long rem; }  ldiv_t; 
typedef struct { long long quot; long long rem; } lldiv_t;

  div_t   div(const      int  numerator, const      int  denominator);
 ldiv_t  ldiv(const      long numerator, const      long denominator);
lldiv_t lldiv(const long long numerator, const long long denominator);

/* __________________________________________________________ STRING PARSING */
   double atof( const char * const str);
      int atoi( const char * const str);
     long atol( const char * const str);
long long atoll(const char * const str);

      float strtof( const char * const str, char **endptr);
     double strtod( const char * const str, char **endptr);
long double strtold(const char * const str, char **endptr);

     long strtol( const char * const str, char **endptr, const int base);
long long strtoll(const char * const str, char **endptr, const int base);

     unsigned long strtoul( const char * const str, char **endptr, const int base);
unsigned long long strtoull(const char * const str, char **endptr, const int base);

#ifdef __cplusplus
}
#endif

#endif
