#include <stdlib.h>

lldiv_t lldiv(const long long numerator, const long long denominator) {
    return (lldiv_t) {
        .quot = numerator / denominator,
        .rem = numerator % denominator
    };
}
