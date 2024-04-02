all: clean c_standardlib c_object asm_object image

clean:
	rm -rf *.o
c_standardlib:
	gcc -m32 -fno-stack-protector -fno-builtin -c util/standardlib/ctype.c -o ctype.o
	gcc -m32 -fno-stack-protector -fno-builtin -c util/standardlib/string.c -o string.o

c_object:
	gcc -m32 -fno-stack-protector -fno-builtin -c main.c -o main.o
	gcc -m32 -fno-stack-protector -fno-builtin -c util/console.c -o console.o
	gcc -m32 -fno-stack-protector -fno-builtin -c util/util.c -o util.o
	gcc -m32 -fno-stack-protector -fno-builtin -c hardware/gdt.c -o gdt.o
	gcc -m32 -fno-stack-protector -fno-builtin -c hardware/idt.c -o idt.o
	gcc -m32 -fno-stack-protector -fno-builtin -c hardware/interrupt.c -o interrupt.o
	gcc -m32 -fno-stack-protector -fno-builtin -c hardware/pic.c -o pic.o
	gcc -m32 -fno-stack-protector -fno-builtin -c hardware/pit.c -o pit.o
	gcc -m32 -fno-stack-protector -fno-builtin -c hardware/keyboard.c -o keyboard.o

asm_object:
	nasm -f elf32 multiboot.asm -o kernel.o
	nasm -f elf32 hardware/gdt.asm -o agdt.o
	nasm -f elf32 hardware/idt.asm -o aidt.o

image:
	ld -m elf_i386 -T link.ld \
	kernel.o main.o console.o util.o \
	ctype.o string.o \
	gdt.o agdt.o idt.o aidt.o interrupt.o pic.o pit.o \
	keyboard.o \
	-o kernel
	
	mv kernel myos/boot/kernel
	grub-mkrescue -o myos.iso myos/
	rm *.o