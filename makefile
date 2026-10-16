boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin

kernel_entry.o: kernel_entry.asm
	nasm -f elf32 kernel_entry.asm -o kernel_entry.o

isr_stumbs.o: isr_stumbs.asm
	nasm -f elf32 isr_stumbs.asm -o isr_stumbs.o

switch.o: switch.asm
	nasm -f elf32 switch.asm -o switch.o

kernel.o: kernel.c
	gcc -m32 -ffreestanding -fno-stack-protector -fno-pie \
	-c kernel.c -o kernel.o

vga.o: vga.c
	gcc -m32 -ffreestanding -fno-stack-protector  \
	-fno-pie -nostdlib -c vga.c -o vga.o 

paging.o: paging.c
	gcc -m32 -ffreestanding -fno-stack-protector \
	-fno-pie -nostdlib -c paging.c -o paging.o

keyboard.o: keyboard.c
	gcc -m32 -ffreestanding -fno-stack-protector \
	-fno-pie -nostdlib -c keyboard.c -o keyboard.o

idt.o: idt.c
	gcc -m32 -ffreestanding -fno-stack-protector \
	-fno-pie -nostdlib -c idt.c -o idt.o

pic.o: pic.c
	gcc -m32 -ffreestanding -fno-stack-protector \
	-fno-pie -nostdlib -c pic.c -o pic.o

timer.o: timer.c
	gcc -m32 -ffreestanding -fno-stack-protector \
	-fno-pie -nostdlib -c timer.c -o timer.o

task.o: task.c
	gcc -m32 -ffreestanding -fno-stack-protector \
	-fno-pie -nostdlib -c task.c -o task.o

stdlib.o: stdlib.c
	gcc -m32 -ffreestanding -fno-stack-protector \
	-fno-pie -nostdlib -c stdlib.c -o stdlib.o

string.o: string.c
	gcc -m32 -ffreestanding -fno-stack-protector \
	-fno-pie -nostdlib -c string.c -o string.o

powers.o:powers.c
	gcc -m32 -ffreestanding -fno-stack-protector \
	-fno-pie -nostdlib -c powers.c -o powers.o

fpu.o: fpu.c
	gcc -m32 -ffreestanding -fno-stack-protector \
	-fno-pic -nostdlib -c fpu.c -o fpu.o

kernel.bin: kernel_entry.o kernel.o vga.o paging.o \
	keyboard.o idt.o pic.o isr_stumbs.o timer.o switch.o \
	task.o stdlib.o string.o powers.o fpu.o
	ld -m elf_i386 -Ttext 0x10000 --oformat binary \
	kernel_entry.o kernel.o vga.o paging.o keyboard.o \
	idt.o pic.o isr_stumbs.o timer.o switch.o task.o \
	stdlib.o string.o powers.o fpu.o -o kernel.bin

os.img: boot.bin kernel.bin
	cat boot.bin kernel.bin > os.img

run: os.img
	qemu-system-i386 -drive format=raw,file=os.img

clean:
	rm -f *.bin *.o *.img *.elf
	