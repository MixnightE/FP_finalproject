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
            gtk_stack_set_visible_child_name(stack, "EndPage");
        }
    }
    else if (!strcmp(visible_child_name, "BattlePage"))
    {
        Game *game = (Game *)user_data;
        Player *player = game->player;
        Enemy *enemy = game->enemy;
        Field *field = game->field;
        field->round = 0;
        EnemyTable *enemytable = game->enemytable;
        /* 1 : 將deckCard中的牌加入drawCard */
        put_card(&(player->deck));
        int rd = rand() % (game->enemytable->size);
        call_enemy(game->enemy, game->enemytable->data[rd].name);
        printf("enemy: %s\n", enemy->name);
        /* 2 : 載入Enemy圖像 */
        GtkWidget *BattlePage = gtk_stack_get_visible_child(GTK_STACK(stack));
        GList *list = gtk_container_get_children(GTK_CONTAINER(BattlePage));
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
        /* 3 : Round Start */
        round_start((Game *)user_data);
    }
    else if (!strcmp(visible_child_name, "CardPage"))
    {
        Game *game = user_data;
        GtkWidget *CardPage = gtk_stack_get_visible_child(GTK_STACK(stack));
        GList *list = gtk_container_get_children(GTK_CONTAINER(CardPage));
        GtkWidget *ComboText = list->data;
        g_list_free(list);
        gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(ComboText));
        CardDeck deck;
        card_deck_initialize(&deck);
        for (int i = 0; i < 3; i++)
        {
            int rd = rand() % (game->cardtable->size - 6);
            add_card_into_deck(&deck, game->cardtable->data[rd].name);
            char name[101];
            sprintf(name, "%s: %s", deck.card[i].name, deck.card[i].description);
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ComboText), name);
        }
    }
}

void DrawCardDeckButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    // 創造新的GtkDialog顯示卡牌
    GtkWidget *window = ((Game *)data)->window;
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Deck Details", GTK_WINDOW(window), GTK_DIALOG_MODAL, "_OK", GTK_RESPONSE_ACCEPT, NULL);
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    Player *player = ((Game *)data)->player;
    for (int i = 0; i < player->deck.drawCard.size; i++)
    {
        char name[MAX_DESCRIPTION_LENGTH + 1];
        memset(name, 0, sizeof(name));
        strcat(name, player->deck.drawCard.card[i].name);
        strcat(name, ": ");
        strcat(name, player->deck.drawCard.card[i].description);
        GtkWidget *label = gtk_label_new(name);
        gtk_container_add(GTK_CONTAINER(content_area), label);
    }
    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void FoldCardDeckButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    // 創造新的GtkDialog顯示卡牌
    GtkWidget *window = ((Game *)data)->window;
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Deck Details", GTK_WINDOW(window), GTK_DIALOG_MODAL, "_OK", GTK_RESPONSE_ACCEPT, NULL);
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    Player *player = ((Game *)data)->player;
    printf("@@@@@%d\n", player->deck.foldCard.size);
    for (int i = 0; i < player->deck.foldCard.size; i++)
    {
        char name[MAX_DESCRIPTION_LENGTH + 1];
        memset(name, 0, sizeof(name));
        strcat(name, player->deck.foldCard.card[i].name);
        strcat(name, ": ");
        strcat(name, player->deck.foldCard.card[i].description);
        GtkWidget *label = gtk_label_new(name);
        gtk_container_add(GTK_CONTAINER(content_area), label);
    }
    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void HandCardChooseButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    Game *game = (Game *)data;
    GtkComboBoxText *cbox = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(game->builder, "HandCardChooseBox"));
    char name[MAX_NAME_LENGTH + 1];
    char *str = gtk_combo_box_text_get_active_text(cbox);
    if (str == NULL)
        return;
    int len = strlen(str);
    int i;
    for (i = 0; i < len && str[i] != ':'; i++)
        name[i] = str[i];
    name[i] = '\0';
    printf("card name: %s\n", name);
    player_choose_card(game->player, game->enemy, game->field, game->cardtable, name); // 這邊會結算玩家對敵人造成的傷害以及buff
    hp_update(game);
    buff_update(game);
    GtkWidget *energy_label = GTK_WIDGET(gtk_builder_get_object(game->builder, "PlayerEnergyLabel"));
    char player_energy[20];
    sprintf(player_energy, "Energy: %d", game->player->energy);
    gtk_label_set_text(GTK_LABEL(energy_label), player_energy);
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(cbox));
    Player *player = game->player;
    for (int i = 0; i < game->player->deck.handCard.size; i++)
    {
        char name[MAX_DESCRIPTION_LENGTH + 1];
        memset(name, 0, sizeof(name));
        strcat(name, player->deck.handCard.card[i].name);
        strcat(name, ": ");
        strcat(name, player->deck.handCard.card[i].description);
        gtk_combo_box_text_append_text(cbox, name);
    }
}

void CardChooseButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    Game *game = (Game *)data;
    GtkComboBoxText *cbox = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(game->builder, "CardChooseBox"));
    char name[MAX_NAME_LENGTH + 1];
    char *str = gtk_combo_box_text_get_active_text(cbox);
    int len = strlen(str);
    int i;
    for (i = 0; i < len && str[i] != ':'; i++)
        name[i] = str[i];
    name[i] = '\0';
    DEBUG
    printf("card name: %s\n", name);
    add_card_into_deck(&(game->player->deck.deckCard), name);
    DEBUG
    gtk_stack_set_visible_child_name(GTK_STACK(game->stack), "PathPage");
}

void BattleRoundEndButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    Game *game = data;
    round_end(game);
    // 將手牌的ui清光
}

void BattleRoundNextButton_clicked_cb(GtkWidget *widget, gpointer data)
{
    // 結束敵人的回合，開啟新的回合
    round_start((Game *)data);
}

void event_button_clicked(GtkButton *button, gpointer data)
{
    gtk_stack_set_visible_child_name(GTK_STACK(data), "EventPage");
}

void battle_button_clicked(GtkButton *button, gpointer data)
{
    gtk_stack_set_visible_child_name(GTK_STACK(data), "BattlePage");
}

void LoseButton_clicked_cb(GtkButton *button, gpointer data)
{
    gtk_stack_set_visible_child_name(GTK_STACK(data), "MainPage");
}

void BackButton_clicked_cb(GtkButton *button, gpointer data)
{
    gtk_stack_set_visible_child_name(GTK_STACK(data), "MainPage");
}

void EventChooseButton1_clicked_cb(GtkButton *button, gpointer data)
{
    Game *game = (Game *)data;
    game->player->hp += (game->player->hp > (game->player->max_hp - 6) ? game->player->max_hp - game->player->hp : 6);
    gtk_stack_set_visible_child_name(GTK_STACK(game->stack), "PathPage");
}

void EventChooseButton2_clicked_cb(GtkButton *button, gpointer data)
{
    Game *game = (Game *)data;
    game->player->hp -= 6;
    if (game->player->hp <= 0)
        gtk_stack_set_visible_child_name(GTK_STACK(game->stack), "LosePage");
    else
        gtk_stack_set_visible_child_name(GTK_STACK(game->stack), "CardPage");
}

void EndButton_clicked_cb(GtkButton *button, gpointer data)
{
    gtk_stack_set_visible_child_name(GTK_STACK(data), "MainPage");
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

void WinButton_clicked_cb(GtkButton *button, gpointer data)
{
    gtk_stack_set_visible_child_name(GTK_STACK(data), "CardPage");
}