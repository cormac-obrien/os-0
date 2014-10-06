# ARCHITECTURE-SPECIFIC BUILD DIRECTORY
ARCH_DIR:=src/kernel/arch/i386

# ARCHIVER SETTINGS
AR:=i686-elf-ar

# ASSEMBLER SETTINGS
AS:=nasm -felf
ASFLAGS:=

# COMPILER AND LINKER SETTINGS
CC:=i686-elf-gcc
CFLAGS:=-ffreestanding -O2 -std=c11 -Wall -Wextra --sysroot=sysroot/ -isystem=/usr/include
LDFLAGS:=-ffreestanding -O2 -nostdlib -lgcc

# GLOBAL CONSTRUCTORS
CRTI_OBJ:=$(ARCH_DIR)/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=$(ARCH_DIR)/crtn.o

LIBC_OBJS:=\
src/libc/string/strlen.o \

# ARCHITECTURE-SPECIFIC KERNEL COMPONENTS
KERNEL_ARCH_OBJS:=\
$(ARCH_DIR)/boot.o \

# ALL KERNEL COMPONENTS
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

# Objects to be remove by `clean`
OBJS_FOR_DELETION:=\
$(LIBC_OBJS) \
$(KERNEL_OBJS) \
$(CRTI_OBJ) \
$(CRTN_OBJ) \

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
	mkdir -p sysroot/usr/include
	cp src/libc/include/string.h sysroot/usr/include/

libc.a: $(LIBC_OBJS)
	$(AR) rvs $@ $(LIBC_OBJS)

install-libs: libc.a $(LIBC_OBJS)
	mkdir -p sysroot/lib
	mv libc.a sysroot/lib/

install: install-headers install-libs os-0.bin
	mkdir -p sysroot/boot/grub
	cp res/iso/efi.img sysroot/
	cp os-0.bin sysroot/boot/
	cp res/iso/grub.cfg sysroot/boot/grub/

iso: install
	grub-mkrescue -o os-0.iso sysroot/

os-0.bin: $(OBJ_LINK_LIST)
	$(CC) -T $(ARCH_DIR)/linker.ld -o $@ $(LDFLAGS) $^

# GENERIC TARGETS ==============================================================

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

# UTILITY TARGETS ==============================================================

clean:
	rm -f os-0.bin $(OBJS_FOR_DELETION) *.iso *.a
	rm -rf sysroot/
