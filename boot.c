#include <tty/vgatext/tty.h>
#include <asm/asms.h>

void main(void){
	struct tty term;
	vgatext_newtty(&term);
	term.clear(&term);
	/*
	while(1){
		for(int i=32; i<127; i++){
			term.putc(&term, i);
			outb(0x03F8, i);
			for(int i=0; i<4000000; i++);
		}
	}
	*/
	term.puts(&term, "Hello world!\n");
	
	term.putc(&term, inb(0x03F8));
	
	return;
}
