#include <display/vgatext/vgatext.h>

int vgatext_getcapabilities(struct display *self){
	(void)(self);
	return DISPLAY_CAP_TEXT;
}

int vgatext_initializecapability(struct display *self, void *thing, int capability){
	(void)(self);
	if(capability==DISPLAY_CAP_TEXT)
		vgatext_newtext(thing);
	else
		return 1;
	
	return 0;
}

void vgatext_setchar(struct display_text *self, int x, int y, char ch){
	short *tbuf=(short *)self->tbuf;
	char tattr=(self->bg<<4)|(self->fg&0x0f);
	if(x<=self->width && y<=self->height)
		tbuf[y*self->width+x]=ch|(tattr<<8);
}

char vgatext_getchar(struct display_text *self, int x, int y){
	short *tbuf=(short *)self->tbuf;
	return tbuf[y*self->width+x];
}

void vgatext_newtext(struct display_text *self){
	newtext(self);
	self->height=25;
	self->width=80;
	self->fg=7;
	self->bg=0;
	self->tbuf=(char *)0x0B8000;
	self->setchar=vgatext_setchar;
	self->getchar=vgatext_getchar;
	
	return;
}

