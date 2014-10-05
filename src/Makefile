CC=i686-elf-gcc

CFLAGS=-ffreestanding -O2 -std=c11 -Wall -Wextra
ASFLAGS=-felf
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

.PHONY: clean

os-0.bin: boot.o kernel.o
	$(CC) -T kernel/arch/i386/linker.ld -o $@ $(LDFLAGS) $^

boot.o:
	nasm $(ASFLAGS) -o $@ kernel/arch/i386/boot.s 

kernel.o:
	$(CC) $(CFLAGS) -c kernel/kernel.c -o $@

clean:
	rm -f os-0.bin boot.o kernel.o
