#include <stdlib.h>

/* returns the absolute value of n. */
long long llabs(const long long n) {
    return n < 0 ? -n : n;
}
