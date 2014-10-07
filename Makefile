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
CFLAGS:=-ffreestanding -O2 -std=c11 -Wall -Wextra --sysroot=sysroot/ -isystem=/usr/include
LIBK_CFLAGS:=$(CFLAGS) -ffreestanding -fbuiltin
LDFLAGS:=-ffreestanding -O2 -nostdlib -lgcc

# Global constructors
CRTI_OBJ:=$(ARCH_DIR)/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=$(ARCH_DIR)/crtn.o

HOSTED_OBJS:=\

FREE_OBJS:=\
src/libc/string/memcmp.o \
src/libc/string/memcpy.o \
src/libc/string/memmove.o \
src/libc/string/memset.o \
src/libc/string/strlen.o \

LIBC_OBJS:=\
$(FREE_OBJS) \

LIBK_OBJS:=$(FREE_OBJS:.o=.libk.o)

# Architecture-specific kernel components
KERNEL_ARCH_OBJS:=\
$(ARCH_DIR)/boot.o \

# All kernel components
KERNEL_OBJS:=\
$(KERNEL_ARCH_OBJS) \
src/kernel/kernel.o

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

.PHONY: clean install install-headers iso

# INSTALL TARGETS ==============================================================

# INSTALL ORDER:
# - Copy headers to sysroot/usr/include/
# - Compile libc source
# - Archive libc source in sysroot/usr/lib/libc.a
# - Compile kernel modules using sysroot/ resources
# - Link kernel with global constructors in os-0.bin
# - Move boot resources (grub.cfg, efi.img) to sysroot/
# - Run grub-mkrescue on sysroot/

install-headers:
	mkdir -pv $(INCLUDE_DIR)
	cp -v src/libc/include/string.h $(INCLUDE_DIR)

libc.a: $(FREE_OBJS)
	$(AR) rcs $@ $(FREE_OBJS)

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
	$(CC) -T $(ARCH_DIR)/linker.ld -o $@ $(LDFLAGS) $^

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
