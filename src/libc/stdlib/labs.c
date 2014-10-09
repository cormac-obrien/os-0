#include <stdlib.h>

/* returns the absolute value of n. */
long labs(const long n) {
    return n < 0 ? -n : n;
}
