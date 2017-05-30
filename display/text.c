#include <display/text.h>

void dummy_setchar(struct display_text *self, int x, int y, char ch){
	(void)(x);
	(void)(y);
	(void)(self);
	(void)(ch);
	return;
}
char dummy_getchar(struct display_text *self, int x, int y){
	(void)(x);
	(void)(y);
	(void)(self);
	return '7';
}
void display_text_setcolor(struct display_text *self, int fg, int bg){
	self->bg=bg;
	self->fg=fg;
	return;
}
void display_text_putc(struct display_text *self, char ch){
	int cursorchange=0;
	
	/* TODO: handle these */
	if(ch=='\a');/* Bell */
	else if(ch=='\b')/* Backspace */
		cursorchange-=self->cursorx?-1:0;
	else if(ch=='\t')/* tab TODO: tabstops */
		cursorchange+=DISPLAY_TEXT_TABSIZE;
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
void display_text_puts(struct display_text *self, char *str){
	while(*str)
		self->putc(self, *str++);
	return;
}
void display_text_clearterm(struct display_text *self){
	for(int ix=0; ix<self->width; ix++)
		for(int iy=0; iy<self->height-1; iy++)
			self->setchar(self, ix, iy, ' ');
	self->cursorx=0;/* Should these be here? */
	self->cursory=0;
	return;
}
void newtext(struct display_text *self){
	*self=(struct display_text){
		.setchar=dummy_setchar,
		.getchar=dummy_getchar,
		.setcolor=display_text_setcolor,
		.putc=display_text_putc,
		.puts=display_text_puts,
		.clear=display_text_clearterm,
	};
	return;
}

