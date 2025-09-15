# ============================
# OSENGINE MAKEFILE (C++)
# ============================

# Kompilator i linker
CXX = g++
AS  = nasm
LD  = ld

# Flagi kompilatora
CXXFLAGS = -m32 -ffreestanding -fno-builtin -fno-stack-protector \
           -fno-rtti -fno-exceptions -Wall -Wextra
ASFLAGS  = -f elf
LDFLAGS  = -melf_i386

# Katalogi
SRC_DIR  = .
CPP_DIR  = cpp
H_DIR    = h
DATA_DIR = data

# Pliki źródłowe C++
CPP_SOURCES = \
	$(CPP_DIR)/framebuffer.cpp \
	$(CPP_DIR)/image.cpp \
	$(DATA_DIR)/ose/kernel.cpp

# Obiekty wynikowe
OBJECTS = $(CPP_SOURCES:.cpp=.o)

# Nazwy wyjściowe
KERNEL = mykernel.bin
ISO    = mykernel.iso

# ============================
# Reguły
# ============================

all: $(ISO)

# Kompilacja plików C++
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(H_DIR) -c $< -o $@

# Kompilacja plików asm (jeśli będą)
%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

# Linkowanie kernela
$(KERNEL): $(OBJECTS)
	$(LD) $(LDFLAGS) -Ttext 0x1000 -o $@ $(OBJECTS)

# Tworzenie ISO z GRUB
$(ISO): $(KERNEL)
	rm -rf iso
	mkdir -p iso/boot/grub
	cp $(KERNEL) iso/boot/
	echo 'set timeout=0'        >  iso/boot/grub/grub.cfg
	echo 'set default=0'       >> iso/boot/grub/grub.cfg
	echo 'menuentry "OSENGINE" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot2 /boot/$(KERNEL)' >> iso/boot/grub/grub.cfg
	echo '  boot'              >> iso/boot/grub/grub.cfg
	echo '}'                   >> iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso
	rm -rf iso

# Uruchomienie w QEMU
run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

# Porządki
clean:
	rm -f $(OBJECTS) $(KERNEL) $(ISO)

.PHONY: all clean run
