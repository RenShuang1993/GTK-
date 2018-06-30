#ifndef _menucallbacks_
#define _menucallbacks_

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

/***************************************************************** PROTOTYPES */
void message_dialog (GSimpleAction *action, GVariant *parameter, gpointer data);
void quit_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void open_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void save_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void rotate_c_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void rotate_counter_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void flip_h_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void flip_v_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void about_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void histogram_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void open_file(char*filename);
void get_pixel(GtkWidget *window_new);
void pixel(guchar *daten_r,guchar *daten_g,guchar *daten_b,guchar *daten_grey,GtkWidget *window_new);
int max_value(guchar *value);
void about_clicked (GtkWidget * widget, gpointer data);
void save_clicked (char*filename, gpointer data);
void rotate_c (gpointer data);
void rotate_counter (gpointer data);
void flip_h (gpointer data);
void flip_v (gpointer data);
#endif


