C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)

OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o cpu/gdt_init.o}

CC = gcc
CCFLAGS = -m32 -ffreestanding
XORRISO = --xorriso="./xorriso/xorriso/xorriso" # Needed in labs 

AS := nasm # Deal with it
ASFLAGS := -f elf32 # ELF binary in multiboot format ... mmm ... yummy

LD := ld
LDFLAGS := -melf_i386 
LDFILE := link.ld

MKRESCUE := grub2-mkrescue # On your system it might be called differently


# Build Process 
all: iso

kernel.bin: multiboot-header.o kernel-entry.o ${OBJ}
	$(LD) $(LDFLAGS) -T  $(LDFILE) $^ -o $@ 

kernel-entry.o: kernel-entry.asm
	$(AS) $(ASFLAGS) $< -o $@

iso: kernel.bin
	mkdir -p .isodir/boot/grub
	cp kernel.bin .isodir/boot/
	cp grub.cfg .isodir/boot/grub
	$(MKRESCUE) $(XORRISO) -o myos.iso .isodir

# Generics 
%.o: %.c ${HEADERS}
	${CC} ${CCFLAGS} -c $< -o $@

%.o: %.asm
	${AS} ${ASFLAGS} $< -o $@

clean:
	rm -f *.o *.iso *.bin .isodir/boot/kernel.bin  kernel/*.o drivers/*.o cpu/*.o libc/*.o

