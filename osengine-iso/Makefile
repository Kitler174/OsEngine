GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386 -L/usr/lib/i386-linux-gnu
# Tworzymy obiekty z binarek
data/images/%.o: data/images/%.bin
	ld -r -b binary $< -o $@
IMAGE_BINARIES := $(wildcard data/images/*.bin)
IMAGE_OBJECTS := $(IMAGE_BINARIES:.bin=.o)
data/music/%.o: data/music/%.bin
	ld -r -b binary $< -o $@
MUSIC_BINARIES := $(wildcard data/music/*.bin)
MUSIC_OBJECTS := $(MUSIC_BINARIES:.bin=.o)

objects = loader.o cpp/image.o data/ose/kernel.o cpp/framebuffer.o
objects += $(IMAGE_OBJECTS) $(MUSIC_OBJECTS)
%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

cpp/%.o: cpp/%.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects) 

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

mykernel.iso: mykernel.bin
	rm -rf iso

	mkdir -p iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "CatOS" {' >> iso/boot/grub/grub.cfg
	echo '  insmod usb' >> iso/boot/grub/grub.cfg
	echo '  insmod usbms' >> iso/boot/grub/grub.cfg
	echo '  insmod usbmouse' >> iso/boot/grub/grub.cfg
	echo '  insmod vbe' >> iso/boot/grub/grub.cfg
	echo '  insmod gfxterm' >> iso/boot/grub/grub.cfg
	echo '  terminal_output gfxterm' >> iso/boot/grub/grub.cfg
	echo '  set gfxpayload=1024x768x32' >> iso/boot/grub/grub.cfg
	echo '  multiboot2 /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '  boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso
	cat iso/boot/grub/grub.cfg
	ls iso/boot/grub
	rm -rf iso

run: mykernel.iso
	qemu-system-i386 -cdrom mykernel.iso

# =========================
# MULTITASK DEMO SECTION
# =========================

# Kompilacja context switch asm
context_switch.o: context_switch.asm
	nasm -f elf $< -o $@

# Kompilacja multitaskingu
task.o: task.c
	gcc -m32 -c $< -o $@

main.o: main.c
	gcc -m32 -c $< -o $@

multitask: main.o task.o context_switch.o
	gcc -m32 -o $@ $^

run-multitask: multitask
	./multitask

.PHONY: install run run-multitask