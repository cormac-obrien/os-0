# README #

OS-0 aims to be a minimalist Unix-like system for Intel x86 architectures.

The operating system is currently nothing more than a skeleton, but it will
boot successfully under GRUB2 and should work under any multiboot-compliant
bootloader, though others have not been tested.

### Dependencies###

- A GCC cross-compiler toolchain for i686-elf
- QEMU (for the `run-qemu` script)

### Building OS-0 ###

Build and run OS-0 by navigating to the `src/` directory and running

```
#!shell

$ make iso
```

I would strongly recommend against booting this on the metal as it hasn't
undergone much bug testing yet, but in theory it should work. It boots and runs
successfully on QEMU, and the `run-qemu` script will boot the system assuming
you've built the ISO and have QEMU installed.

The binaries and object files can then be removed with

```
#!shell

$ make clean
```
