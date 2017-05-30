#ifndef DISPLAY_H
#define DISPLAY_H

/* This is supposed to be some bit field shit, but we only have one thing atm, so, yeah */
#define DISPLAY_CAP_TEXT 1

struct display{
	/* Returns a bitwise or of display capabilities */
	int (*getcapabilities)(struct display *self);
	/*
	  Initializes thing depending on capability
	  On success, returns 0 and fills thing with the specified thing
	  TODO: error codes
	  For example, getinterface(self, display_text_thing, DISPLAY_CAP_TEXT);
	  Initializes display_text_thing and returns 0 on success, or returns something else
	  and leaves thing alone
	 */
	int (*initializecapability)(struct display *self, void *thing, int capability);
};

#endif
