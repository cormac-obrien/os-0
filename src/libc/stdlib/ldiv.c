#include <stdlib.h>

ldiv_t ldiv(const long numerator, const long denominator) {
    return (ldiv_t){
        .quot = numerator / denominator,
        .rem = numerator % denominator
    };
}
