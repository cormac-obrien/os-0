X86:=i686-elf

ARCH:=$(X86)

# Build directories
ARCH_DIR:=src/kernel/arch/$(ARCH)
BOOT_DIR:=sysroot/boot
INCLUDE_DIR:=sysroot/usr/include
LIB_DIR:=sysroot/usr/lib

AR:=$(X86)-ar
CC:=$(X86)-gcc
LD:=$(X86)-ld

# Compiler and linker settings
CFLAGS:=\
-ffreestanding \
-g \
-isystem=usr/include \
-masm=intel \
-O2 \
-std=gnu99 \
-Wall \
-Wextra \
--sysroot=sysroot/
CPPFLAGS:=
LIBK_CFLAGS:=$(CFLAGS) -fbuiltin
LDFLAGS:=-ffreestanding -O2 -nostdlib -lgcc

CRTI_OBJ:=$(ARCH_DIR)/crti.o # ============================ Global constructors
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=$(ARCH_DIR)/crtn.o

# libc objects with system dependencies
HOSTED_LIBC_OBJS:=\

# libc objects with no system dependencies
FREE_LIBC_OBJS:=\
src/libc/math/log10.o \
src/libc/stdio/printf.o \
src/libc/stdio/printint.o \
src/libc/stdio/puts.o \
src/libc/stdlib/abort.o \
src/libc/string/memcmp.o \
src/libc/string/memcpy.o \
src/libc/string/memmove.o \
src/libc/string/memset.o \
src/libc/string/strlen.o \

# all libc objects
LIBC_OBJS:=\
$(HOSTED_LIBC_OBJS) \
$(FREE_LIBC_OBJS) \

LIBC_HEADERS:=\
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
src/kernel/kernel/kernel_early.o \
src/kernel/kernel/kernel_main.o \
src/kernel/kernel/kernel_putchar.o \
src/kernel/kernel/kernel_puts.o \
src/kernel/vga.o \

KERNEL_HEADERS:=\
src/kernel/include/kernel.h \
src/kernel/include/multiboot.h \
src/kernel/include/vga.h \
$(ARCH_DIR)/include/arch.h \

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

install-headers:
	mkdir -pv $(INCLUDE_DIR)
	cp -v $(LIBC_HEADERS) $(INCLUDE_DIR)
	cp -v $(KERNEL_HEADERS) $(INCLUDE_DIR)
	mkdir -pv $(INCLUDE_DIR)/sys
	cp -v $(LIBC_SYS_HEADERS) $(INCLUDE_DIR)/sys

libc.a: $(LIBC_OBJS)
	$(AR) rcs $@ $(LIBC_OBJS)

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

os-0.bin: $(OBJ_LINK_LIST)
	$(CC) -T $(ARCH_DIR)/linker.ld -o $@ $(LDFLAGS) $^ -L $(LIB_DIR) -lk

iso: clean install run-qemu
	grub-mkrescue -o os-0.iso sysroot/

run-qemu:
	echo -e "#!/bin/sh\n\nqemu-system-i386 -m 128 -cdrom os-0.iso" >> run-qemu
	chmod +x run-qemu

# GENERIC TARGETS ==============================================================

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

%.o: %.s
	nasm -felf $< -o $@

%.libk.o: %.c
	$(CC) $(LIBK_CFLAGS) -c $< -o $@

# UTILITY TARGETS ==============================================================

clean:
	rm -f os-0.bin $(OBJS_FOR_DELETION) *.iso *.a run-qemu
	rm -rf sysroot/
