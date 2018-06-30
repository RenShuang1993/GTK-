#include "gnomemenu.h"
#include "menucallbacks.h"

/************************ MESSAGE INFO DIALOG that prints the selected action */
extern GtkWidget *IMG;
extern GtkWidget *headerbar;
extern GtkWidget *box;
GdkPixbuf *dst;
GtkWidget *image;
void
message_dialog (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	const gchar *name;
	GtkWidget *dialog;
	widgets *a = (widgets *) data;

	name = g_action_get_name (G_ACTION (action));
	dialog = gtk_message_dialog_new (GTK_WINDOW (a->window),
					 GTK_DIALOG_DESTROY_WITH_PARENT,
					 GTK_MESSAGE_INFO,
					 GTK_BUTTONS_CLOSE,
					 "%s:Renshuang-Image Editor",
					 name);
	g_signal_connect (dialog, "response",
			  G_CALLBACK (gtk_widget_destroy), NULL);
	gtk_widget_show (dialog);
    about_clicked(NULL,(gpointer) a);
}

/****************************************************************** CALLBACKS */
void
quit_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
    
	g_application_quit (G_APPLICATION (a->app));
}

void
open_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
    GtkWidget *dialog;
    GtkFileFilter *filter;
    //filter
    filter = gtk_file_filter_new();
    gtk_file_filter_add_pixbuf_formats(filter);
    gtk_file_filter_set_name(filter,"Bildformate");
    //
    GtkFileChooserAction Action= GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    a->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    dialog = gtk_file_chooser_dialog_new("Open File",
                                                                              GTK_WINDOW(a->window),
                                                                              Action,
                                                                              ("_Cancel"),
                                                                              GTK_RESPONSE_CANCEL,
                                                                              ("_Open"),
                                                                              GTK_RESPONSE_ACCEPT,
                                                                              NULL);
   gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog),filter);                                                                        
  res = gtk_dialog_run(GTK_DIALOG(dialog));
  if(res==GTK_RESPONSE_ACCEPT){
	  char *filename;
	  GtkFileChooser* chooser=GTK_FILE_CHOOSER(dialog);
	  filename=gtk_file_chooser_get_filename(chooser);
	  open_file(filename);
	  g_free(filename);
	  }
gtk_widget_destroy(dialog);
}

void
save_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
  GtkWidget *dialog;

   GtkFileChooser* chooser;
 
    GtkFileChooserAction Action= GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;
    a->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    dialog = gtk_file_chooser_dialog_new("Save",
                                                                              GTK_WINDOW(a->window),
                                                                              Action,
                                                                              ("_Cancel"),
                                                                              GTK_RESPONSE_CANCEL,
                                                                              ("_Save"),
                                                                              GTK_RESPONSE_ACCEPT,
                                                                              NULL);
   
         chooser = GTK_FILE_CHOOSER(dialog);
	   gtk_file_chooser_set_do_overwrite_confirmation(chooser,TRUE);             
  res = gtk_dialog_run(GTK_DIALOG(dialog));
  if(res==GTK_RESPONSE_ACCEPT){
	  char *filename;
	 
	  filename=gtk_file_chooser_get_filename(chooser);
	  gdk_pixbuf_save(dst,filename,"png",NULL,NULL);
      save_clicked (filename,(gpointer)a);
	  g_free(filename);
	  }
gtk_widget_destroy(dialog);

	
}

void
rotate_c_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
	if(image != NULL){
    gtk_container_remove(GTK_CONTAINER(box),image);
    }
    else {
	  return;
    }
	GdkPixbuf *src = gdk_pixbuf_scale_simple(dst,700,700,GDK_INTERP_BILINEAR);
	dst = gdk_pixbuf_rotate_simple(src,GDK_PIXBUF_ROTATE_CLOCKWISE);
	image = gtk_image_new_from_pixbuf(dst);
	gtk_box_set_center_widget(GTK_BOX(box),image);
	g_object_unref(src);
	rotate_c((gpointer)a);
    gtk_widget_show_all(IMG);
}

void
rotate_counter_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
   if(image != NULL){
    gtk_container_remove(GTK_CONTAINER(box),image);
    }
    else {
	  return;
    }
    //box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	//gtk_container_add(GTK_CONTAINER(IMG),box);
	GdkPixbuf *src = gdk_pixbuf_scale_simple(dst,700,700,GDK_INTERP_BILINEAR);
	dst = gdk_pixbuf_rotate_simple(src,GDK_PIXBUF_ROTATE_COUNTERCLOCKWISE);
	image = gtk_image_new_from_pixbuf(dst);
	gtk_box_set_center_widget(GTK_BOX(box),image);
    rotate_counter((gpointer)a);
	g_object_unref(src);
    gtk_widget_show_all(IMG);
	
}

void
flip_h_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
    if(image != NULL){
    gtk_container_remove(GTK_CONTAINER(box),image);
    }
    else {
	  return;
    }
	GdkPixbuf *src = gdk_pixbuf_scale_simple(dst,700,700,GDK_INTERP_BILINEAR);
	dst = gdk_pixbuf_flip(src,TRUE);
	image = gtk_image_new_from_pixbuf(dst);
	gtk_box_set_center_widget(GTK_BOX(box),image);
    flip_h ((gpointer)a);
	g_object_unref(src);
    gtk_widget_show_all(IMG);
}

void
flip_v_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
    if(image != NULL){
    gtk_container_remove(GTK_CONTAINER(box),image);
    }
    else {
	  return;
    }
	GdkPixbuf *src = gdk_pixbuf_scale_simple(dst,700,700,GDK_INTERP_BILINEAR);
	dst = gdk_pixbuf_flip(src,FALSE);
	image = gtk_image_new_from_pixbuf(dst);
	gtk_box_set_center_widget(GTK_BOX(box),image);
    flip_v ((gpointer)a);
	g_object_unref(src);
    gtk_widget_show_all(IMG);
}

void
about_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;

	message_dialog (action, NULL, (gpointer) a);
	
}

void
histogram_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	if(dst==NULL){
        g_print("NO IMAGE");
        return;
    }
    widgets *a = (widgets *) data;
    a->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (a->window), "Histogram");
    gtk_window_set_position (GTK_WINDOW (a->window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size (GTK_WINDOW (a->window),255,510);
    get_pixel(a->window);
    gtk_widget_show_all (GTK_WIDGET (a->window));
	
}
void
get_pixel(GtkWidget *window_new){
	int n_channels,rowstride,width,height;
	guchar *pixels,*p;
	n_channels = gdk_pixbuf_get_n_channels(dst);
	width = gdk_pixbuf_get_width(dst);
	rowstride = gdk_pixbuf_get_rowstride (dst);
	height = gdk_pixbuf_get_height (dst);
	int i;
	int k;
	guchar histo_r[255]={0};
	guchar histo_g[255]={0};
	guchar histo_b[255]={0};
	guchar histo_grey[255]={0};
	guchar grey;
	pixels = gdk_pixbuf_get_pixels (dst);
	  for(i=0; i<height; i++){
        for(k=0; k<width; k++){
            p = pixels + i * rowstride + k * n_channels;
          histo_r[p[0]]+=1;
          histo_g[p[1]]+=1;
          histo_b[p[2]]+=1;
          grey = p[0]*0.2126+p[1]*0.7152+p[2]*0.0722;
          histo_grey[grey]+=1;
        }
    }
   guchar *daten_r=(guchar*)g_malloc(3*255*255);
   guchar *daten_g=(guchar*)g_malloc(3*255*255);
   guchar *daten_b=(guchar*)g_malloc(3*255*255);
   guchar *daten_grey=(guchar*)g_malloc(3*255*255);
   int max_r=max_value(histo_r);
   int max_g=max_value(histo_g);
   int max_b=max_value(histo_b);
   int max_grey=max_value(histo_grey);
   float x;
   /************red_histogram */
   for(i=0; i<255; i++){
	   
        for(k=0; k<255; k++){
			x=255-((float)histo_r[k]/histo_r[max_r])*255;
			if(k==max_r){
		      daten_r[i*3*255+3*k]=255;
		      daten_r[i*3*255+3*k+1]=0;
		      daten_r[i*3*255+3*k+2]=0;
	        }
	        else if(x<=i){
			  daten_r[i*3*255+3*k]=255;
		      daten_r[i*3*255+3*k+1]=0;
		      daten_r[i*3*255+3*k+2]=0;
			}
			else{
			daten_r[i*3*255+3*k]=255;
		    daten_r[i*3*255+3*k+1]=255;
		    daten_r[i*3*255+3*k+2]=255;
			}
		}
	}
    /************green_histogram */
	for(i=0; i<255; i++){
	   
        for(k=0; k<255; k++){
			x=255-((float)histo_g[k]/histo_g[max_g])*255;
			if(k==max_g){
		      daten_g[i*3*255+3*k]=0;
		      daten_g[i*3*255+3*k+1]=255;
		      daten_g[i*3*255+3*k+2]=0;
	        }
	        else if(x<=i){
			  daten_g[i*3*255+3*k]=0;
		      daten_g[i*3*255+3*k+1]=255;
		      daten_g[i*3*255+3*k+2]=0;
			}
			else{
			daten_g[i*3*255+3*k]=255;
		    daten_g[i*3*255+3*k+1]=255;
		    daten_g[i*3*255+3*k+2]=255;
			}
		}
	}
	/************blue_histogram */
	for(i=0; i<255; i++){
        for(k=0; k<255; k++){
			x=255-((float)histo_b[k]/histo_b[max_b])*255;
			if(k==max_b){
		      daten_b[i*3*255+3*k]=0;
		      daten_b[i*3*255+3*k+1]=0;
		      daten_b[i*3*255+3*k+2]=255;
	        }
	        else if(x<=i){
			  daten_b[i*3*255+3*k]=0;
		      daten_b[i*3*255+3*k+1]=0;
		      daten_b[i*3*255+3*k+2]=255;
			}
			else{
			daten_b[i*3*255+3*k]=255;
		    daten_b[i*3*255+3*k+1]=255;
		    daten_b[i*3*255+3*k+2]=255;
			}
		}
	}
	/************grey_histogram */
	for(i=0; i<255; i++){
        for(k=0; k<255; k++){
			x=255-((float)histo_grey[k]/histo_grey[max_grey])*255;
			if(k==max_grey){
		      daten_grey[i*3*255+3*k]=0;
		      daten_grey[i*3*255+3*k+1]=0;
		      daten_grey[i*3*255+3*k+2]=0;
	        }
	        else if(x<=i){
			  daten_grey[i*3*255+3*k]=0;
		      daten_grey[i*3*255+3*k+1]=0;
		      daten_grey[i*3*255+3*k+2]=0;
			}
			else{
			daten_grey[i*3*255+3*k]=255;
		    daten_grey[i*3*255+3*k+1]=255;
		    daten_grey[i*3*255+3*k+2]=255;
			}
		}
	}
   pixel(daten_r,daten_g,daten_b,daten_grey,window_new);
   g_free (daten_r);
   g_free (daten_g);
   g_free (daten_b);
   g_free (daten_grey);
	}
void pixel(guchar *daten_r,guchar *daten_g,guchar *daten_b,guchar *daten_grey,GtkWidget *window_new){
	GtkWidget *h_box;
	GdkPixbuf *red;
	GdkPixbuf *green;
	GdkPixbuf *blue;
	GdkPixbuf *grey;
	h_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
	gtk_container_add(GTK_CONTAINER(window_new),h_box);
	red = gdk_pixbuf_new_from_data(daten_r,GDK_COLORSPACE_RGB,FALSE,8,256,256,3*255,NULL,NULL);
	green = gdk_pixbuf_new_from_data(daten_g,GDK_COLORSPACE_RGB,FALSE,8,256,256,3*255,NULL,NULL);
	blue = gdk_pixbuf_new_from_data(daten_b,GDK_COLORSPACE_RGB,FALSE,8,256,256,3*255,NULL,NULL);
	grey = gdk_pixbuf_new_from_data(daten_grey,GDK_COLORSPACE_RGB,FALSE,8,256,256,3*255,NULL,NULL);
	GtkWidget *image_r = gtk_image_new_from_pixbuf(red);
	GtkWidget *image_g = gtk_image_new_from_pixbuf(green);
	GtkWidget *image_b = gtk_image_new_from_pixbuf(blue);
	GtkWidget *image_grey = gtk_image_new_from_pixbuf(grey);
	gtk_container_add(GTK_CONTAINER(h_box),image_r);
	gtk_container_add(GTK_CONTAINER(h_box),image_g);
	gtk_container_add(GTK_CONTAINER(h_box),image_b);
	gtk_container_add(GTK_CONTAINER(h_box),image_grey);
	//gtk_widget_show_all(h_box);
	}
int max_value(guchar *value){
    int i;
    int k=0;
    guchar max=value[0];
    for(i=0;i<255;i++){
	 if(value[i]>max){
		 max=value[i];
		 k=i; 
	}
	}
	return k;
}
void 
open_file(char*filename){
	if (box == NULL){
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    }
    if(image != NULL){
    gtk_container_remove(GTK_CONTAINER(box),image);
    }
    else{
	gtk_container_add(GTK_CONTAINER(IMG),box);
    }
	GdkPixbuf *src= gdk_pixbuf_new_from_file(filename,NULL);
	dst=gdk_pixbuf_scale_simple(src,700,700,GDK_INTERP_BILINEAR);
	image = gtk_image_new_from_pixbuf(dst);
	//free
	g_object_unref(src);
	gtk_box_set_center_widget(GTK_BOX(box),image);
	gtk_header_bar_set_subtitle (GTK_HEADER_BAR (headerbar),filename);
	gtk_widget_show_all(IMG);
    
	}
 void
about_clicked (GtkWidget * widget, gpointer data)
{
	widgets * w = (widgets *) data;
	gchar * msg = g_malloc (256);
	static gint cnt = 1;

	g_snprintf (msg, 256, " about is clicked %d ", cnt++);
	gtk_statusbar_push (GTK_STATUSBAR (w->statusbar), w->id, msg);
}
 void
save_clicked (char*filename, gpointer data)
{
	widgets * w = (widgets *) data;
	gchar * msg = g_malloc (256);
	g_snprintf (msg, 256, " saved as %s ", filename);
	gtk_statusbar_push (GTK_STATUSBAR (w->statusbar), w->id, msg);
}
void rotate_c (gpointer data){
    widgets * w = (widgets *) data;
    gchar * msg = g_malloc (256);
	static gint cnt = 1;

	g_snprintf (msg, 256, " Rotate clockwise %d ", cnt++);
	gtk_statusbar_push (GTK_STATUSBAR (w->statusbar), w->id, msg);
    }
void rotate_counter (gpointer data){
    widgets * w = (widgets *) data;
    gchar * msg = g_malloc (256);
	static gint cnt = 1;

	g_snprintf (msg, 256, " Rotate counterclockwise %d ", cnt++);
	gtk_statusbar_push (GTK_STATUSBAR (w->statusbar), w->id, msg);
    }
void flip_h (gpointer data){
    widgets * w = (widgets *) data;
    gchar * msg = g_malloc (256);
	static gint cnt = 1;

	g_snprintf (msg, 256, " Flip horizontally %d ", cnt++);
	gtk_statusbar_push (GTK_STATUSBAR (w->statusbar), w->id, msg);
    }
void flip_v (gpointer data){
    widgets * w = (widgets *) data;
    gchar * msg = g_malloc (256);
	static gint cnt = 1;

	g_snprintf (msg, 256, " Flip vertically %d ", cnt++);
	gtk_statusbar_push (GTK_STATUSBAR (w->statusbar), w->id, msg);
    }
/** EOF */
