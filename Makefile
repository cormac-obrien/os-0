CC=i686-elf-gcc

CFLAGS=-ffreestanding -O2 -std=c11 -Wall -Wextra
ASFLAGS=-felf
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

.PHONY: clean

os-0.bin: boot.o kernel.o
	$(CC) -T src/kernel/arch/i386/linker.ld -o $@ $(LDFLAGS) $^
	rm -f boot.o kernel.o

boot.o:
	nasm $(ASFLAGS) -o $@ src/kernel/arch/i386/boot.s 

kernel.o:
	$(CC) $(CFLAGS) -c src/kernel/kernel.c -o $@

clean:
	rm -f os-0.bin boot.o kernel.o *.iso
	rm -rf sysroot/

iso: os-0.bin
	mkdir -p sysroot/boot/grub
	cp res/iso/efi.img sysroot/
	cp os-0.bin sysroot/boot/
	cp res/iso/grub.cfg sysroot/boot/grub/
	grub-mkrescue -o os-0.iso sysroot/
