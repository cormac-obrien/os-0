#include <stdlib.h>
#include <sys/cdefs.h>

__attribute__((__noreturn__))
void abort(void) {
    // TODO: Kernel panic
    printf("PICNIC\n");
    for(;;) { }
    __builtin_unreachable();
}
