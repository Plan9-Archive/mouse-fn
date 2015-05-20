/* Copyright (c) 2015 David Hoskin <davidrhoskin@gmail.com> */

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <stdio.h>

/* Works fine for p9p acme, but grab inherently takes focus on every keypress. */
/* This breaks things like Firefox menus. */

/* Todo: hjkl? */

#define F1 67
#define F2 68
#define F3 69
#define F(k) (k-F1+1)

/* Todo: use XK_Pointer_Button1 etc, or at least XK_F1. */

int buttons[3];

void
key(XKeyEvent e)
{
	/*printf("key f%d %s\n", F(e.keycode), e.type == KeyPress? "down": "up");*/
	XTestFakeButtonEvent(e.display, F(e.keycode), e.type == KeyPress, 0);
	return;
}

int
main(void)
{
	Display *d;
	Window root;
	XEvent e;
	int f;
	int er;

	d = XOpenDisplay(NULL);
	if(d == NULL){
		perror("could not open display");
		return 1;
	}
	root = DefaultRootWindow(d);

	for(f = F1; f <= F3; ++f)
		XGrabKey(d, f, AnyModifier, root, 1, GrabModeAsync, GrabModeAsync);

	while(!XNextEvent(d, &e)){
		if(e.type == KeyPress || e.type == KeyRelease)
			key(e.xkey);
		else
			printf("unknown event %d\n", e.type);
	}

	return 0;
}

