#include <math.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel.h>

int printint(const intmax_t arg) {
    const size_t len = (size_t)log10((double)arg);
    char str[len + 1];

    for (size_t i = len - 1; i < len; --i) { // ends on underflow
        str[i] = i % 10;
        i /= 10;
    }

    str[len] = '\0';
    kernel_puts(str);

    return 0;
}
