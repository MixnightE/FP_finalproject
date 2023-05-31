#include <gtk/gtk.h>

signed main(int argc, char *argv[])
{
    GtkWidget *window;

    // init gtk
    gtk_init(&argc, &argv);

    // create main, top level, window.
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // set window title.
    gtk_window_set_title(GTK_WINDOW(window), "Hello, GTK+");

    // connect the destroy signal of the window to gtk_main_quit
    // when the window is about to be destroyed
    // we get a notification and stop the main GTK+ loop.
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *label;

    // create the "Hello World." label.
    label = gtk_label_new("Hello, World.\n");

    // insert it into main window.
    gtk_container_add(GTK_CONTAINER(window), label);

    // make sure everything are visible.
    gtk_widget_show_all(window);

    // start main loop, and let it rest there until the app is closed.
    gtk_main();

    return 0;
}