#nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o -ffreestanding
ld -m elf_i386 -T link.ld -o new/boot/kernel.bin kasm.o kc.o
qemu-system-i386 -kernel new/boot/kernel.bin
#grub-mkrescue -o myOS.iso new/

