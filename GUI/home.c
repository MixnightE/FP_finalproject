#include <gtk/gtk.h>
#define DEBUG printf("Running at %s, %d line\n", __FILE__, __LINE__);

typedef struct EventParamData
{
    GtkWidget *stack;  // 儲存介面的堆疊
    GtkWidget *window; // 儲存視窗
} EventParam;

void start_button_clicked(GtkWidget *widget, gpointer data)
{
    GtkWidget *stack = ((EventParam *)data)->stack;
    g_print("Start Button Clicked.\n");
    // 切換至遊戲介面
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "path");
}

void setting_button_clicked(GtkWidget *widget, gpointer data)
{
    g_print("Setting Button Clicked.\n");
    // 切換至設定介面
}

void quit_button_clicked(GtkWidget *widget, gpointer data)
{
    g_print("Quit Button Clicked.\n");
    gtk_main_quit();
}

void event_button_clicked(GtkButton *button, gpointer data)
{
    GtkWidget *stack = ((EventParam *)data)->stack;
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "event");
}

void battle_button_clicked(GtkButton *button, gpointer data)
{
    GtkWidget *stack = ((EventParam *)data)->stack;
    GtkWidget *window = ((EventParam *)data)->window;
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "battle");
    gtk_widget_set_name(window, "BattleWindow");
}

// 將名為image_name的圖檔導入，回傳GtkImage物件
GtkWidget *scale_image(const char *image_name, int new_width /*新的寬度*/)
{
    GError *error = NULL;

    GdkPixbuf *original_pixbuf = gdk_pixbuf_new_from_file(image_name, &error);
    if (!original_pixbuf)
    {
        g_printerr("Error loading file '%s': %s\n", image_name, error->message);
        g_error_free(error);
        return NULL;
    }

    int original_width = gdk_pixbuf_get_width(original_pixbuf);
    int original_height = gdk_pixbuf_get_height(original_pixbuf);

    // 确定新的尺寸，保持宽高比不变
    int new_height = (new_width * original_height) / original_width; // 根据比例计算新高度

    // 创建新的缩放后的图像
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(original_pixbuf, new_width, new_height, GDK_INTERP_BILINEAR);

    // 在不再需要原图像时释放它
    g_object_unref(original_pixbuf);

    // 创建新的GtkImage部件
    GtkWidget *image = gtk_image_new_from_pixbuf(scaled_pixbuf);

    // 在创建GtkImage部件后，释放缩放后的图像
    g_object_unref(scaled_pixbuf);

    // 现在你可以返回这个缩放后的图像了
    return image;
}

GtkWidget *create_main_menu(EventParam *action)
{
    // 創建一個垂直的 box 來裝按鈕
    GtkWidget *bbox = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_CENTER);

    // 創建 "開始遊戲"、"設置" 和 "退出遊戲" 按鈕
    GtkWidget *start_button = gtk_button_new_with_label("開始遊戲");
    gtk_style_context_add_class(gtk_widget_get_style_context(start_button), "MainButtonClass");
    g_signal_connect(start_button, "clicked", G_CALLBACK(start_button_clicked), action);
    GtkWidget *setting_button = gtk_button_new_with_label("設置");
    gtk_style_context_add_class(gtk_widget_get_style_context(setting_button), "MainButtonClass");
    g_signal_connect(setting_button, "clicked", G_CALLBACK(setting_button_clicked), action);
    GtkWidget *quit_button = gtk_button_new_with_label("退出遊戲");
    gtk_style_context_add_class(gtk_widget_get_style_context(quit_button), "MainButtonClass");
    g_signal_connect(quit_button, "clicked", G_CALLBACK(quit_button_clicked), NULL);
    // 將按鈕添加到 vbox 中
    gtk_container_add(GTK_CONTAINER(bbox), start_button);
    gtk_container_add(GTK_CONTAINER(bbox), setting_button);
    gtk_container_add(GTK_CONTAINER(bbox), quit_button);
    return bbox;
}

GtkWidget *create_path_choice_view(EventParam *action)
{
    // 創建一個新的 GtkBox 作為容器
    GtkWidget *bbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    GtkWidget *button[3];
    for (int i = 0; i < 3; i++)
    {
        int rd = rand() % 2;
        if (rd)
        {
            button[i] = gtk_button_new_with_label("事件");
            g_signal_connect(GTK_BUTTON(button[i]), "clicked", G_CALLBACK(event_button_clicked), action);
            gtk_style_context_add_class(gtk_widget_get_style_context(button[i]), "MainButtonClass");
        }
        else
        {
            button[i] = gtk_button_new_with_label("戰鬥");
            g_signal_connect(GTK_BUTTON(button[i]), "clicked", G_CALLBACK(battle_button_clicked), action);
            gtk_style_context_add_class(gtk_widget_get_style_context(button[i]), "MainButtonClass");
        }
        gtk_container_add(GTK_CONTAINER(bbox), button[i]);
    }

    return bbox;
}

GtkWidget *create_battle_view()
{
    GtkWidget *grid = gtk_grid_new();

    GtkWidget *player_image = scale_image("./image/Player.png", 300);
    if (!player_image)
    {
        fprintf(stderr, "scale image error: \"./image/Player.png\"\n");
        exit(1);
    }
    gtk_grid_attach(GTK_GRID(grid), player_image, 0, 0, 1, 1);
    // GtkWidget *player_hand = create_player_hand();
    // gtk_grid_attach(GTK_GRID(grid), player_hand, 0, 1, 1, 1);

    GtkWidget *enemy_image = scale_image("./image/Mouse.png", 300);
    if (!enemy_image)
    {
        fprintf(stderr, "scale image error: \"./image/Mouse.png\"\n");
        exit(1);
    }
    gtk_grid_attach(GTK_GRID(grid), enemy_image, 1, 0, 1, 1);

    GtkWidget *settings_button = gtk_button_new_with_label("設置");
    g_signal_connect(GTK_BUTTON(settings_button), "clicked", G_CALLBACK(setting_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), settings_button, 1, 2, 1, 1);

    GtkWidget *quit_button = gtk_button_new_with_label("保存並退出");
    g_signal_connect(GTK_BUTTON(quit_button), "clicked", G_CALLBACK(quit_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), quit_button, 1, 3, 1, 1);

    return grid;
}

// GtkWidget *create_setting_view()
// {
// }

signed main(int argc, char *argv[])
{

    // init gtk
    gtk_init(&argc, &argv);
    srand(time(NULL));

    // create main, top level, window.
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // set window name to available style
    gtk_widget_set_name(window, "MainWindow");

    // set window title
    gtk_window_set_title(GTK_WINDOW(window), "Roguelike Game");

    // set window size.
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);

    // connect the destroy signal of the window to gtk_main_quit
    // when the window is about to be destroyed
    // we get a notification and stop the main GTK+ loop.
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /* load background image to window */

    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    if (!gtk_css_provider_load_from_path(provider, "./style/MainWindow.css", NULL))
    {
        g_print("Error loading CSS file\n");
        return 1;
    }
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 1000);

    EventParam action;
    action.stack = stack;
    action.window = window;

    GtkWidget *main_interface = create_main_menu(&action);
    gtk_stack_add_titled(GTK_STACK(stack), main_interface, "main", "Main Menu");

    GtkWidget *path_interface = create_path_choice_view(&action);
    gtk_stack_add_titled(GTK_STACK(stack), path_interface, "path", "Path Choose");

    // GtkWidget *setting_view = create_setting_view();
    // gtk_stack_add_titled(GTK_STACK(stack), setting_view, "setting", "Setting Menu");

    // GtkWidget *event_interface = create_event_view();
    // gtk_stack_add_titled(GTK_STACK(stack), event_interface, "event", "Event");

    GtkWidget *battle_interface = create_battle_view();
    gtk_stack_add_titled(GTK_STACK(stack), battle_interface, "battle", "Battle");

    gtk_container_add(GTK_CONTAINER(window), stack);

    // make sure everything are visible.
    gtk_widget_show_all(window);

    // start main loop, and let it rest there until the app is closed.
    gtk_main();

    return 0;
}