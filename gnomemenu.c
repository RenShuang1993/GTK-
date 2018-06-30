#include "gnomemenu.h"
#include "menucallbacks.h"

/******************************************************************** GLOBALS */
GtkWidget *IMG;
GtkWidget *headerbar;
gchar **argv;
gint argc;
GtkWidget *box;

// map menu actions to callbacks
const GActionEntry app_actions[] = {
	{ "open", open_callback, NULL, NULL, NULL },
	{ "save", save_callback, NULL, NULL, NULL },
	{ "rotate_c", rotate_c_callback, NULL, NULL, NULL },
	{ "quit", quit_callback, NULL, NULL, NULL },
	{ "rotate_counter", rotate_counter_callback, NULL, NULL, NULL},
	{ "flip_h", flip_h_callback, NULL, NULL, NULL},
	{ "flip_v", flip_v_callback, NULL, NULL, NULL},
	{ "about", about_callback, NULL, NULL, NULL},
	{ "histogram", histogram_callback, NULL, NULL, NULL}
};

/****************************************************** FILE LOCAL PROTOTYPES */
static void
construct_menu (GtkApplication *app,gpointer data);


/*********************************************************************** Menu */
static void
construct_menu (GtkApplication *app,gpointer data)
{
    
	// the application menu displayed in the GNOME panel
	GMenu *appmenu;
	GMenu *editmenu;

	GtkWidget *openbutton;
	GtkWidget *savebutton;

	// the menu displayed as a popover below the gears button
	GMenu *gearmenu;
	GtkWidget *gearmenubutton;
	GtkWidget *aboutbutton;
	GtkWidget *gearicon;
	GtkWidget *gearicon_a;
   
	widgets *a = (widgets *) data;
    /* Statusbar */
    GtkStyleContext *context;
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;
	a->statusbar = gtk_statusbar_new();
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    
	gtk_widget_set_size_request (a->statusbar, 100, 10);
	gtk_box_pack_start (GTK_BOX (box), a->statusbar, FALSE, FALSE, 0);
	a->id = gtk_statusbar_get_context_id (GTK_STATUSBAR (a->statusbar), "demo");
	context = gtk_widget_get_style_context (a->statusbar);
    /* style the statusbar text using a color */
	provider = gtk_css_provider_new ();
	display = gdk_display_get_default ();
	screen = gdk_display_get_default_screen (display);
	gtk_style_context_add_provider_for_screen (screen,
						   GTK_STYLE_PROVIDER (provider),
						   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider),
					 " GtkStatusbar {\n"
					 "   color: green;\n"
					 "}\n", -1, NULL);
	g_object_unref (provider);
	// create a headerbar
	headerbar = gtk_header_bar_new ();
	gtk_widget_show (headerbar);
	gtk_header_bar_set_title (GTK_HEADER_BAR (headerbar), "Image editor");
	gtk_window_set_titlebar (GTK_WINDOW (a->window), headerbar);
	
// create and fill in the application menu in the GNOME panel
	appmenu = g_menu_new();
	g_menu_append (appmenu, "About", "app.about");
	g_menu_append (appmenu, "_Quit", "app.quit");
	aboutbutton = gtk_menu_button_new();
	gearicon_a  = gtk_image_new_from_icon_name ("face-angel",
						 GTK_ICON_SIZE_SMALL_TOOLBAR);
	gtk_button_set_image (GTK_BUTTON (aboutbutton), gearicon_a);
	gtk_header_bar_pack_end (GTK_HEADER_BAR (headerbar), aboutbutton);
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (aboutbutton),
					G_MENU_MODEL (appmenu));
	//g_object_unref (appmenu);
					
	// create an OPEN button, add it to the headerbar and connect the callbacks
	openbutton = gtk_button_new_with_label ("Open");
	gtk_header_bar_pack_start (GTK_HEADER_BAR (headerbar), openbutton);
	gtk_actionable_set_action_name (GTK_ACTIONABLE (openbutton), "app.open");

	// create the gear menu button
	gearmenubutton = gtk_menu_button_new();
	gearicon = gtk_image_new_from_icon_name ("emblem-system-symbolic",
						 GTK_ICON_SIZE_SMALL_TOOLBAR);
	gtk_button_set_image (GTK_BUTTON (gearmenubutton), gearicon);
	gtk_header_bar_pack_end (GTK_HEADER_BAR (headerbar), gearmenubutton);
	// create a menu for the gear button
	gearmenu = g_menu_new();
	g_menu_append (gearmenu, "Save ", "app.save");
	editmenu = g_menu_new();
	g_menu_append (editmenu, "_Rotate Clockwise", "app.rotate_c");
	g_menu_append (editmenu, "_Rotate Counterclockwise", "app.rotate_counter");
	g_menu_append (editmenu, "_Flip Horizontally", "app.flip_h");
	g_menu_append (editmenu, "_Flip Vertically", "app.flip_v");
	g_menu_append (editmenu, "_Display Histogram", "app.histogram");
	g_menu_append_section (gearmenu, NULL, G_MENU_MODEL (editmenu));
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (gearmenubutton),
					G_MENU_MODEL (gearmenu));
   g_object_unref (appmenu);
   g_object_unref (editmenu);
	g_object_unref (gearmenu);
	
	
}
/****************************************************************/

/**************************************************************** MAIN WINDOW */
static void
activate (GtkApplication *app, GApplicationCommandLine *cmdline,gpointer data)
{

	widgets *a = (widgets *) data;
	
    argv = g_application_command_line_get_arguments (cmdline, &argc);
    a->filename = argv[1];
  
	a->window = gtk_application_window_new (app);
	IMG=a->window;
	gtk_window_set_application (GTK_WINDOW (a->window), GTK_APPLICATION (app));
	//gtk_window_set_title (GTK_WINDOW (a->window), "GNOME Menu Demo");
	gtk_window_set_position (GTK_WINDOW (a->window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW (a->window), 700,700);
	gtk_window_set_default_icon_from_file ("icon.png", NULL);

	/* moved the creation of the menu to a dedicated function */
    construct_menu (app,(gpointer) a);
    if(a->filename!=NULL){
	open_file(a->filename);
    }
	g_strfreev (argv);

	gtk_widget_show_all (GTK_WIDGET (a->window));
	

}

/*********************************************************** STARTUP CALLBACK */
static void
startup (GApplication *app, gpointer data)
{
	widgets *a = (widgets *) data;
	// connect actions with callbacks
	g_action_map_add_action_entries (G_ACTION_MAP (app), app_actions,
					 G_N_ELEMENTS (app_actions), (gpointer) a);
}
/*********************************************************************** main */
int
main (int argc, char **argv)
{
	int status;
	widgets *a = g_malloc (sizeof (widgets));

	a->app = gtk_application_new ("org.gtk.gnomemenu-Wunused-parameter",G_APPLICATION_HANDLES_COMMAND_LINE);
	
	g_signal_connect (a->app, "command-line", G_CALLBACK (activate), (gpointer) a);
	
	g_signal_connect (a->app, "startup", G_CALLBACK (startup), (gpointer) a);
	status = g_application_run (G_APPLICATION (a->app), argc, argv);
	g_object_unref (a->app);
	g_free (a);
	return status;
}
/** EOF */
