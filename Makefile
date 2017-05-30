# The CC needs to be changed. For whatever reason, make wasn't using the PATH
CC=~/x-tools/i386-unknown-elf/bin/i386-unknown-elf-gcc -g -O0 -std=c99 -pedantic -Wall -Wextra \
-Werror -I. -ffreestanding -nostdlib

kernel all: asms.o init.o boot.o text.o vgatext.o
	$(CC) -T boot.ld asms.o init.o boot.o text.o vgatext.o -o kernel 

init.o: # The very start
	nasm -f elf32 asm/init.s -o init.o

asms.o: 
	nasm -f elf32 asm/asms.s -o asms.o

boot.o: # We have C!
	$(CC) -c boot.c

vgatext.o: 
	$(CC) -c display/vgatext/vgatext.c -o vgatext.o

text.o: 
	$(CC) -c display/text.c -o text.o

run: 
	qemu-system-i386 -kernel kernel -gdb tcp::1234 #-S

clean:
	rm -f vgatext.o text.o boot.o init.o asms.o kernel
