#ifndef TTY_H
#define TTY_H

#define TTY_TABSIZE 8

struct tty{
	int height;
	int width;
	int cursorx;
	int cursory;
	int fg;
	int bg;
	char *tbuf;/* Not to be used directly. Driver-specific? */
	
	void (*setchar)(struct tty *self, int x, int y, char ch);
	char (*getchar)(struct tty *self, int x, int y);
	void (*setcolor)(struct tty *self, int fg, int bg);
	void (*putc)(struct tty *self, char ch);
	void (*puts)(struct tty *self, char *str);
	void (*clear)(struct tty *self);
};

void dummy_setchar(struct tty *self, int x, int y, char ch);
char dummy_getchar(struct tty *self, int x, int y);
void tty_setcolor(struct tty *self, int fg, int bg);
void tty_putc(struct tty *self, char ch);
void tty_puts(struct tty *self, char *str);
void tty_clearterm(struct tty *self);
void newtty(struct tty *self);

#endif
