#include <callback.h>

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *stack;

    /* 从 Glade 文件加载 user interface */
    builder = gtk_builder_new_from_file("./GUI/GtkApp.glade");
    gtk_builder_connect_signals(builder, user_data);

    /* 获取 'GtkApplicationWindow' 的实例 */
    window = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
    stack = GTK_WIDGET(gtk_builder_get_object(builder, "MainStack"));

    Game *game = user_data;
    game->builder = builder;
    game->window = window;
    game->stack = stack;

    /* 确保 'GtkApplicationWindow' 知道它属于哪个 'GtkApplication' */
    gtk_window_set_application(GTK_WINDOW(window), app);

    gtk_widget_show_all(window);

    // g_object_unref(builder);
}

signed main(int argc, char *argv[])
{
    /* Gtk data */

    GtkApplication *app;
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    /* Default data */

    Player player;
    Enemy enemy;
    Field field;
    CardTable cardtable;
    EnemyTable enemytable;
    BuffTable bufftable;

    /* Default Data Initialization */
    all_initialize(&player, &enemy, &field, &cardtable, &enemytable, &bufftable);

    /* Init GTK+ */
    gtk_init(&argc, &argv);
    srand(time(NULL));

    /* -------------- CSS Style -------------- */
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider), "./GUI/style.css", NULL);
    /* -------------------------------------- */

    int status;

    Card card;
    Game game;
    game_initialize(&game, &card, &player, &enemy, &field, &cardtable, &bufftable, &enemytable);

#if __APPLE__
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
#elif __linux__
    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
#else
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
#endif
    g_signal_connect(app, "activate", G_CALLBACK(activate), &game);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}