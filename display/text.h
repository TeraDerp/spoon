#ifndef TEXT_H
#define TEXT_H

#include <display/display.h>

#define DISPLAY_TEXT_TABSIZE 8

struct display_text{
	int height;
	int width;
	int cursorx;
	int cursory;
	int fg;
	int bg;
	char *tbuf;/* Not to be used directly. Driver-specific? */
	
	void (*setchar)(struct display_text *self, int x, int y, char ch);
	char (*getchar)(struct display_text *self, int x, int y);
	void (*setcolor)(struct display_text *self, int fg, int bg);/* TODO: standardize colors */
	void (*putc)(struct display_text *self, char ch);
	void (*puts)(struct display_text *self, char *str);
	void (*clear)(struct display_text *self);
};

void dummy_setchar(struct display_text *self, int x, int y, char ch);
char dummy_getchar(struct display_text *self, int x, int y);
void display_text_setcolor(struct display_text *self, int fg, int bg);
void display_text_putc(struct display_text *self, char ch);
void display_text_puts(struct display_text *self, char *str);
void display_text_clearterm(struct display_text *self);
void newtext(struct display_text *self);

#endif
