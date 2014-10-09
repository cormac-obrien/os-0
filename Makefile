# Build directories
ARCH_DIR:=src/kernel/arch/i386
BOOT_DIR:=sysroot/boot
INCLUDE_DIR:=sysroot/usr/include
LIB_DIR:=sysroot/usr/lib

# Archiver settings
AR:=i686-elf-ar

# Assembler settings
AS:=nasm -felf
ASFLAGS:=

# Compiler and linker settings
CC:=i686-elf-gcc
CFLAGS:=-ffreestanding -O2 -std=c11 -Wall -Wextra --sysroot=sysroot/ -isystem=usr/include
LIBK_CFLAGS:=$(CFLAGS) -ffreestanding -fbuiltin
LDFLAGS:=-ffreestanding -O2 -nostdlib -lgcc

# Global constructors
CRTI_OBJ:=$(ARCH_DIR)/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=$(ARCH_DIR)/crtn.o

# libc objects with system dependencies
HOSTED_LIBC_OBJS:=\

# libc objects with no system dependencies
FREE_LIBC_OBJS:=\
src/libc/stdio/printf.o \
src/libc/stdio/puts.o \
src/libc/stdlib/abort.o \
src/libc/stdlib/abs.o \
src/libc/stdlib/div.o \
src/libc/stdlib/ldiv.o \
src/libc/stdlib/lldiv.o \
src/libc/stdlib/labs.o \
src/libc/stdlib/llabs.o \
src/libc/string/memcmp.o \
src/libc/string/memcpy.o \
src/libc/string/memmove.o \
src/libc/string/memset.o \
src/libc/string/strlen.o \

# all libc objects
LIBC_OBJS:=\
$(FREE_LIBC_OBJS) \
$(HOSTED_LIBC_OBJS) \

LIBC_HEADERS:=\
src/libc/include/errno.h \
src/libc/include/math.h \
src/libc/include/stdio.h \
src/libc/include/stdlib.h \
src/libc/include/string.h \

LIBC_SYS_HEADERS:=\
src/libc/include/sys/cdefs.h \

LIBK_OBJS:=$(FREE_LIBC_OBJS:.o=.libk.o)

# Architecture-specific kernel components
KERNEL_ARCH_OBJS:=\
$(ARCH_DIR)/boot.o \

# All kernel components
KERNEL_OBJS:=\
$(KERNEL_ARCH_OBJS) \
src/kernel/kernel/kernel.o \
src/kernel/vga/vga_color.o \
src/kernel/vga/vga_cell.o \
src/kernel/vga/vga_init.o \
src/kernel/vga/vga_putcell.o \
src/kernel/vga/vga_setcolor.o \

KERNEL_HEADERS:=\
src/kernel/include/kernel.h \
src/kernel/include/multiboot.h \
src/kernel/include/vga.h \

# Objects to be linked into the final kernel
OBJ_LINK_LIST:=\
$(CRTI_OBJ) \
$(CRTBEGIN_OBJ) \
$(KERNEL_OBJS) \
$(CRTEND_OBJ) \
$(CRTN_OBJ) \

# Objects to be removed by `make clean`
OBJS_FOR_DELETION:=\
$(LIBC_OBJS) \
$(LIBK_OBJS) \
$(KERNEL_OBJS) \
$(CRTI_OBJ) \
$(CRTN_OBJ) \

BINARIES:=libc.a libg.a libk.a

ALL_HEADERS:=\
$(LIBC_HEADERS) \
$(KERNEL_HEADERS) \

.PHONY: clean install install-headers iso

# INSTALL TARGETS ==============================================================

# INSTALL ORDER:
# - Copy headers to sysroot/usr/include/
# - Compile libc source into libraries and move to /sysroot/usr/lib
# - Compile kernel modules using sysroot/ resources
# - Link kernel with global constructors in os-0.bin
# - Move boot resources (grub.cfg, efi.img) to sysroot/
# - Run grub-mkrescue on sysroot/

install-headers:
	mkdir -pv $(INCLUDE_DIR)
	cp -v $(LIBC_HEADERS) $(INCLUDE_DIR)
	cp -v $(KERNEL_HEADERS) $(INCLUDE_DIR)
	mkdir -pv $(INCLUDE_DIR)/sys
	cp -v $(LIBC_SYS_HEADERS) $(INCLUDE_DIR)/sys

libc.a: $(FREE_LIBC_OBJS)
	$(AR) rcs $@ $(FREE_LIBC_OBJS)

libg.a:
	$(AR) rcs $@

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

install-libs: $(BINARIES)
	mkdir -pv $(LIB_DIR)
	mv -v $(BINARIES) $(LIB_DIR)

install: install-headers install-libs os-0.bin
	mkdir -pv $(BOOT_DIR)/grub
	cp -v res/iso/efi.img sysroot/
	cp -v os-0.bin $(BOOT_DIR)/
	cp -v res/iso/grub.cfg $(BOOT_DIR)/grub/

iso: install
	grub-mkrescue -o os-0.iso sysroot/

os-0.bin: $(OBJ_LINK_LIST)
	$(CC) -T $(ARCH_DIR)/linker.ld -o $@ $(LDFLAGS) $^ -L sysroot/usr/lib -lk -lg -lc

# GENERIC TARGETS ==============================================================

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.libk.o: %.c
	$(CC) $(LIBK_CFLAGS) -c $< -o $@

# UTILITY TARGETS ==============================================================

clean:
	rm -f os-0.bin $(OBJS_FOR_DELETION) *.iso *.a
	rm -rf sysroot/
