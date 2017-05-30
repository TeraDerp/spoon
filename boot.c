#include <display/vgatext/vgatext.h>
#include <asm/asms.h>

void main(void){
	struct display display;
	struct display_text term;
	
	/* Pretend these two lines happen in device autodetection or someshit like that */
	display.getcapabilities=vgatext_getcapabilities;
	display.initializecapability=vgatext_initializecapability;
	
	display.initializecapability(&display, &term, DISPLAY_CAP_TEXT);
	
	term.clear(&term);
	
	while(1){
		for(int i=32; i<127; i++){
			term.putc(&term, i);
			outb(0x03F8, i);
			for(int i=0; i<4000000; i++);
		}
	}
	
	term.puts(&term, "Hello world!\n");
	
	term.putc(&term, inb(0x03F8));
	
	return;
}
