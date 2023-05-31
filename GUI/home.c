#include <gtk/gtk.h>

signed main(int argc, char *argv[])
{
    GtkWidget *window;

    // init gtk
    gtk_init(&argc, &argv);

    // create main, top level, window.
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // set window title.
    gtk_window_set_title(GTK_WINDOW(window), "Roguelike Game");

    // set window size.
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 1000);

    GtkWidget *vbox;

    // create new vertical box, objects inside will平均分配空間，間隔為5像素
    vbox = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(vbox), GTK_BUTTONBOX_START);

    GtkWidget *button_start, *button_setting;

    // create "Start" button and "Setting" button.
    button_start = gtk_button_new_with_label("Start");
    button_setting = gtk_button_new_with_label("Setting");

    // add vbox to window.
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // push buttons into under of box.
    gtk_box_pack_start(GTK_BOX(vbox), button_start, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button_setting, TRUE, TRUE, 5);

    // connect the destroy signal of the window to gtk_main_quit
    // when the window is about to be destroyed
    // we get a notification and stop the main GTK+ loop.
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // GtkWidget *label;

    // // create the "Hello World." label.
    // label = gtk_label_new("Hello, World.\n");

    // // insert it into main window.
    // gtk_container_add(GTK_CONTAINER(window), label);

    // make sure everything are visible.
    gtk_widget_show_all(window);

    // start main loop, and let it rest there until the app is closed.
    gtk_main();

    return 0;
}