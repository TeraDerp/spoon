#include <tty/vgatext/tty.h>

void vgatext_setchar(struct tty *self, int x, int y, char ch){
	short *tbuf=(short *)self->tbuf;
	char tattr=(self->bg<<4)|(self->fg&0x0f);
	if(x<=self->width && y<=self->height)
		tbuf[y*self->width+x]=ch|(tattr<<8);
}

char vgatext_getchar(struct tty *self, int x, int y){
	short *tbuf=(short *)self->tbuf;
	return tbuf[y*self->width+x];
}

void vgatext_newtty(struct tty *self){
	newtty(self);
	self->height=25;
	self->width=80;
	self->fg=7;
	self->bg=0;
	self->tbuf=(char *)0x0B8000;
	self->setchar=vgatext_setchar;
	self->getchar=vgatext_getchar;
	
	return;
}

