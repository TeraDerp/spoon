BITS 32
MAGIC equ 0x1BADB002 ; Multiboot magic
FLAGS equ 1
CHECKSUM equ -(MAGIC+FLAGS)

extern main
global _start

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

section .text
_start:
	call main
	hlt
