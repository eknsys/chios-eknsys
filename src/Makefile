CC = gcc
LD = ld
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra

OBJS = boot.o kernel.o mouse.o keyboard.o vga.o ui_input.o ui_button.o p_about.o app.o

all: kernel.bin iso

kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel.o

mouse.o: kernel/mouse.c
	$(CC) $(CFLAGS) -c kernel/mouse.c -o mouse.o

keyboard.o: kernel/keyboard.c
	$(CC) $(CFLAGS) -c kernel/keyboard.c -o keyboard.o

vga.o: kernel/vga.c
	$(CC) $(CFLAGS) -c kernel/vga.c -o vga.o

ui_input.o: kernel/ui_input.c
	$(CC) $(CFLAGS) -c kernel/ui_input.c -o ui_input.o

ui_button.o: kernel/ui_button.c
	$(CC) $(CFLAGS) -c kernel/ui_button.c -o ui_button.o

p_about.o: kernel/p_about.c
	$(CC) $(CFLAGS) -c kernel/p_about.c -o p_about.o

app.o: kernel/app.c
	$(CC) $(CFLAGS) -c kernel/app.c -o app.o

boot.o: kernel/boot.s
	$(CC) $(CFLAGS) -c kernel/boot.s -o boot.o

kernel.bin: $(OBJS)
	$(LD) -m elf_i386 -T kernel/linker.ld -o kernel.bin $(OBJS)

iso:
	cp kernel.bin iso/boot/kernel.bin
	cp iso/boot/grub/grub.cfg iso/boot/grub/grub.cfg

clean:
	rm -f *.o kernel.bin

buildiso:
	cp kernel.bin iso/boot/kernel.bin
	grub-mkrescue -o chios.iso iso

run:
	qemu-system-i386 -cdrom chios.iso
