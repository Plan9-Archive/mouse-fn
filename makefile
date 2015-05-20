CFLAGS += -I/usr/X11R6/include
LDFLAGS += -L/usr/X11R6/lib -lX11 -lXtst

mouse-fn: mouse-fn.c
