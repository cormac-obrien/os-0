# README #

OS-0 is a minimalist Unix-like system for Intel x86 architectures. The operating system is currently nothing more than a skeleton, but it will boot successfully under GRUB2 and should work under any multiboot-compliant bootloader, though others have not been tested.

### Running OS-0 ###

I strongly recommend against trying to boot OS-0 on the metal. QEMU is the development emulator of choice for OS-0, so install it if you don't have it. Most distributions of Linux have it in their official repositories.

Build and run OS-0 with

```
#!shell

$ make && qemu-system-i386 os-0.bin
```