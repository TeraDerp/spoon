#ifndef VGATEXT_TTY_H
#define VGATEXT_TTY_H

#include <tty/tty.h>

void vgatext_setchar(struct tty *self, int x, int y, char ch);
char vgatext_getchar(struct tty *self, int x, int y);
void vgatext_newtty(struct tty *self);

#endif
