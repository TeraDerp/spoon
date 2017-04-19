BITS 32
global inb
global outb

section .text
inb:
	mov dx, [esp+4]; arg1: short port
	in al, dx
	ret
outb:
	mov dx, [esp+4]; arg1: short port
	mov al, [esp+8]; arg2: char val
	out dx, al
	ret
