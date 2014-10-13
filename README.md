# README #

OS-0 aims to be a minimalist Unix-like system for Intel x86 architectures.

### Features & Goals ###
- [x] 16-color, 80x25-character VGA text mode
- [x] Multiboot-based memory map detection
- [x] Stack-based page frame allocation
- [x] Paging
- [ ] Keyboard interrupt handling

### Dependencies ###

- A GCC cross-compiler toolchain (gcc and ld) for i686-elf
- QEMU (for the `run-qemu` script)

### Building OS-0 ###

Build and run OS-0 by navigating to the `src/` directory and running

```
$ make iso
$ ./run-qemu
```

Binaries and object files can then be cleaned up with

```
$ make clean
```

If you want, you can burn the ISO to a disc and boot with that, but I haven't
even tested this on the metal yet, so I would strongly recommend you not do so.

### LICENSE ###
OS-0 is freely available under the MIT license (see LICENSE.txt for more
information). Go crazy.
