#include <tty/tty.h>

void dummy_setchar(struct tty *self, int x, int y, char ch){
	(void)(x);
	(void)(y);
	(void)(self);
	(void)(ch);
	return;
}
char dummy_getchar(struct tty *self, int x, int y){
	(void)(x);
	(void)(y);
	(void)(self);
	return '7';
}
void tty_setcolor(struct tty *self, int fg, int bg){
	self->bg=bg;
	self->fg=fg;
	return;
}
void tty_putc(struct tty *self, char ch){
	int cursorchange=0;
	
	/* TODO: handle these */
	if(ch=='\a');/* Bell */
	else if(ch=='\b')/* Backspace */
		cursorchange-=self->cursorx?-1:0;
	else if(ch=='\t')/* tab TODO: tabstops */
		cursorchange+=TTY_TABSIZE;
	else if(ch=='\n')/* newline */
		cursorchange=self->width;
	else if(ch=='\v');/* vtab */
	else if(ch=='\f');
	else if(ch=='\r')/* carriage return */
		cursorchange-=self->cursorx;
	else if(ch==127);/* DEL */
	else if(ch<127&&ch>31){/* Printable */
		self->setchar(self, self->cursorx, self->cursory, ch);
		cursorchange+=1;
	}else
		return;/* Unprintable... Idkk */
	
	if(!cursorchange)
		return;
	
	if(self->cursorx+cursorchange<self->width)/* Just advance the cursor */
		self->cursorx+=cursorchange;
	else if(self->cursory<self->height-1){/* New line and cursor to the beginning */
		self->cursory+=1;
		self->cursorx=0;
	}else{/* Scroll */
		for(int ix=0; ix<self->width; ix++)/* Copy everything up by a line */
			for(int iy=0; iy<self->height-1; iy++)
				self->setchar(self, ix, iy, self->getchar(self, ix, iy+1));
		
		for(int ix=0; ix<self->width; ix++)/* Clear the final line */
			self->setchar(self, ix, self->height-1, ' ');
		
		self->cursorx=0;
	}
	
	return;
}
void tty_puts(struct tty *self, char *str){
	while(*str)
		self->putc(self, *str++);
	return;
}
void tty_clearterm(struct tty *self){
	for(int ix=0; ix<self->width; ix++)
		for(int iy=0; iy<self->height-1; iy++)
			self->setchar(self, ix, iy, ' ');
	self->cursorx=0;/* Should these be here? */
	self->cursory=0;
	return;
}
void newtty(struct tty *self){
	*self=(struct tty){
		.setchar=dummy_setchar,
		.getchar=dummy_getchar,
		.setcolor=tty_setcolor,
		.putc=tty_putc,
		.puts=tty_puts,
		.clear=tty_clearterm,
	};
	return;
}

