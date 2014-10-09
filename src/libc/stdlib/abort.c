#include <stdio.h>
#include <stdlib.h>
#include <sys/cdefs.h>

#include <vga.h>

__attribute__((__noreturn__))
void abort(void) {
    // TODO: Kernel panic
    vga_init();
    printf("PICNIC\n");
    for(;;) { }
    __builtin_unreachable();
}
