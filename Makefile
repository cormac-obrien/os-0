ARCH_DIR=src/kernel/arch/i386

AS=nasm -felf
CC=i686-elf-gcc

CFLAGS=-ffreestanding -O2 -std=c11 -Wall -Wextra
ASFLAGS=
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

.PHONY: clean install install-headers iso

install: install-headers os-0.bin
	mkdir -p sysroot/boot/grub
	cp res/iso/efi.img sysroot/
	cp os-0.bin sysroot/boot/
	cp res/iso/grub.cfg sysroot/boot/grub/

install-headers:
	mkdir -p sysroot/usr/include
	cp src/libc/include/string.h sysroot/usr/include/

iso: install
	grub-mkrescue -o os-0.iso sysroot/

os-0.bin: boot.o kernel.o
	$(CC) -T $(ARCH_DIR)/linker.ld -o $@ $(LDFLAGS) $^
	rm -f boot.o kernel.o

boot.o:
	$(AS) $(ASFLAGS) -o $@ src/kernel/arch/i386/boot.s 

kernel.o:
	$(CC) $(CFLAGS) -c src/kernel/kernel.c -o $@

clean:
	rm -f os-0.bin boot.o kernel.o *.iso
	rm -rf sysroot/
