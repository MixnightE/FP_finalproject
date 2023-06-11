#include <callback.h>

static int path_counter = 0;

void StartButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    gtk_stack_set_visible_child_name(GTK_STACK(data), "PathPage");
}

void SettingButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    gtk_stack_set_visible_child_name(GTK_STACK(data), "SettingPage");
}

void MainStack_visible_child_name_notify_cb(GObject *gobject, GParamSpec *pspec, gpointer user_data)
{
    path_counter++;
    GtkStack *stack = GTK_STACK(gobject);
    const gchar *visible_child_name = gtk_stack_get_visible_child_name(stack);
    if (!strcmp(visible_child_name, "PathPage"))
    {
        GtkWidget *visible_child = gtk_stack_get_visible_child(stack);
        GList *children, *iter;
        // 得到容器的子小部件列表
        children = gtk_container_get_children(GTK_CONTAINER(visible_child));
        // 遍歷子小部件列表
        for (iter = children; iter != NULL; iter = g_list_next(iter))
        {
            // 移除子小部件
            gtk_container_remove(GTK_CONTAINER(visible_child), GTK_WIDGET(iter->data));
        }
        // 釋放列表
        g_list_free(children);
        if (path_counter <= 10)
        {
            for (int i = 0; i < 3; i++)
            {
                GtkWidget *button;
                int rd = rand() % 2;
                if (rd)
                {
                    button = gtk_button_new_with_label("事件");
                    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(event_button_clicked), stack);
                    gtk_style_context_add_class(gtk_widget_get_style_context(button), "MainButtonClass");
                }
                else
                {
                    button = gtk_button_new_with_label("戰鬥");
                    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(battle_button_clicked), stack);
                    gtk_style_context_add_class(gtk_widget_get_style_context(button), "MainButtonClass");
                }
                gtk_container_add(GTK_CONTAINER(visible_child), button);
                gtk_widget_show(button);
            }
        }
        else
        {
            GtkWidget *button = gtk_button_new_with_label("魔王");
            g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(battle_button_clicked), stack);
            gtk_container_add(GTK_CONTAINER(visible_child), button);
            gtk_widget_show(button);
        }
    }
    if (!strcmp(visible_child_name, "BattlePage"))
    {
        Game *game = (Game *)user_data;
        Player *player = game->player;
        Enemy *enemy = game->enemy;
        Field *field = game->field;
        EnemyTable *enemytable = game->enemytable;
        GtkWidget *BattlePage = gtk_stack_get_visible_child(GTK_STACK(stack));
        GList *list = gtk_container_get_children(GTK_CONTAINER(BattlePage));
        /* 2 : 載入Enemy圖像 */
        GtkWidget *Box = list->next->data;
        g_list_free(list);
        list = gtk_container_get_children(GTK_CONTAINER(Box));
        GtkWidget *enemyImage = list->next->data;
        g_list_free(list);
        char enemyName[51] = "./image/";
        strcat(enemyName, random_enemy_name(enemytable));
        strcat(enemyName, ".png");
        GdkPixbuf *pixbuf = scale_image(enemyName, 300);
        gtk_image_set_from_pixbuf(GTK_IMAGE(enemyImage), pixbuf);
    }
}

void DrawCardDeckButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    // 創造新的GtkDialog顯示卡牌
}

void FoldCardDeckButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    // 創造新的GtkDialog顯示卡牌
}

void BattleRoundEndButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    Game *game = data;
    drop_card(&(game->player->deck));
    // 將手牌的ui清光
}

void BattleRoundNextButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    // 結束敵人的回合，開啟新的回合
}

void event_button_clicked(GtkButton *button, gpointer data)
{
    gtk_stack_set_visible_child_name(GTK_STACK(data), "EventPage");
}

void battle_button_clicked(GtkButton *button, gpointer data)
{
    gtk_stack_set_visible_child_name(GTK_STACK(data), "BattlePage");
}

// 將名為image_name的圖檔導入，回傳GtkImage物件
GdkPixbuf *scale_image(const char *image_name, int new_width /*新的寬度*/)
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
    return scaled_pixbuf;
}