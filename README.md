# README #

OS-0 aims to be a minimalist Unix-like system for Intel x86 architectures.

### Features ###
- 16-color, 80x25-character VGA text mode
- Multiboot-based memory map detection
- Stack-based page frame allocation for up to 4GiB of addressable memory

### Dependencies ###

- A GCC cross-compiler toolchain (gcc and ld) for i686-elf
- QEMU (for the `run-qemu` script)

### Building OS-0 ###

Build and run OS-0 by navigating to the `src/` directory and running

```
$ make iso
```

I would strongly recommend against booting this on the metal as it hasn't
undergone much bug testing yet, but in theory it should work. It boots and runs
successfully on QEMU, and the `run-qemu` script will boot the system assuming
you've built the ISO and have QEMU installed.

The binaries and object files can then be removed with

```
$ make clean
```
