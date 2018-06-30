#ifndef _gnomemenu_
#define _gnomemenu_


#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

typedef struct {
	GtkApplication *app;
	GtkWidget *window;
    GtkWidget *statusbar;
    guint id;
	char *filename;
} widgets;

#endif
