# The CC needs to be changed. For whatever reason, make wasn't using the PATH
CC=~/x-tools/i386-unknown-elf/bin/i386-unknown-elf-gcc -g -O0 -std=c99 -pedantic -Wall -Wextra \
-Werror -I. -ffreestanding -nostdlib

kernel all: asms.o tty.o vgatext.o init.o boot.o
	$(CC) -T boot.ld vgatext.o tty.o asms.o init.o boot.o -o kernel 

init.o: # The very start
	nasm -f elf32 asm/init.s -o init.o

asms.o: 
	nasm -f elf32 asm/asms.s -o asms.o

boot.o: # We have C!
	 $(CC) -c boot.c

tty.o: # Gimme a term!
	$(CC) -c tty/tty.c -o tty.o

vgatext.o: # Backend for tty
	$(CC) -c tty/vgatext/tty.c -o vgatext.o

run: 
	qemu-system-i386 -kernel kernel -gdb tcp::1234 #-S

clean:
	rm -f vgatext.o tty.o boot.o init.o asms.o kernel
