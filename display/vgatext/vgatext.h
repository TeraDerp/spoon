#ifndef VGATEXT_TTY_H
#define VGATEXT_TTY_H

#include <display/text.h>

int vgatext_getcapabilities(struct display *self);
int vgatext_initializecapability(struct display *self, void *thing, int capability);

void vgatext_setchar(struct display_text *self, int x, int y, char ch);
char vgatext_getchar(struct display_text *self, int x, int y);
void vgatext_newtext(struct display_text *self);

#endif
