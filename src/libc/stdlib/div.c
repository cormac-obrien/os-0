#include <stdlib.h>

div_t div(const int numerator, const int denominator) {
    return (div_t){
        .quot = numerator / denominator,
        .rem = numerator % denominator
    };
}
