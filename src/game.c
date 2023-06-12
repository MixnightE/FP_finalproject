#include <game.h>

void all_initialize(Player *player, Enemy *enemy, Field *field, CardTable *cardtable, EnemyTable *enemytable, BuffTable *bufftable)
{
    srand(time(NULL));
    card_table_initialize(cardtable);
    enemy_table_initialize(enemytable);
    buff_table_initialize(bufftable);
    player_initialize(player, 80, 3);
    enemy_initialize(enemy);
    field_initialize(field);

    /* create player cards */

    card_create("Strike", "Deal 6 damage.", TYPE_ATK, 6, 0, 1, Strike, cardtable);
    card_create("Defend", "Gain 5 Block.", TYPE_SKL, 0, 0, 1, Defend, cardtable);
    card_create("Bash", "Deal 8 damage. Apply 2 Vulnerable.", TYPE_ATK, 8, 0, 2, Bash, cardtable);
    card_create("Inflame", "Gain 2 Strength.", TYPE_ABL, 0, 0, 1, Inflame, cardtable);
    card_create("Anger", "Deal 6 damage. Add a copy of this card to the discard pile.", TYPE_ATK, 6, 0, 0, Anger, cardtable);
    card_create("Cleave", "Deal 8 damage.", TYPE_ATK, 8, 0, 1, Cleave, cardtable);
    card_create("Clothesline", "Deal 12 damage. Apply 2 weak.", TYPE_ATK, 12, 0, 2, Clothesline, cardtable);
    card_create("Flex", "Gain 2 strength.", TYPE_SKL, 0, 0, 0, Flex, cardtable);
    card_create("Heavy_Blade", "Deal 14 damage.", TYPE_ATK, 14, 0, 2, Heavy_Blade, cardtable);
    card_create("Iron_Wave", "Gain 5 block. Deal 5 damage.", TYPE_SKL, 5, 0, 1, Iron_Wave, cardtable);
    card_create("Perfected_Strike", "Deal 6 damage. If you have Strike in your deck, deal additional 2 damage.", TYPE_ATK, 6, 0, 2, Perfected_Strike, cardtable);
    card_create("Pommel_Strike", "Deal 9 damage. Draw a card.", TYPE_ATK, 9, 0, 1, Pommel_Strike, cardtable);
    card_create("Shrug_it_Off", "Gain 8 block. Draw a card.", TYPE_SKL, 0, 0, 1, Shrug_it_Off, cardtable);
    card_create("Sword_Boomerang", "Deal 9 damage.", TYPE_ATK, 3, 0, 1, Sword_Boomerang, cardtable);
    card_create("Thunderclap", "Deal 4 damage. Apply 1 vulnerable.", TYPE_ATK, 8, 0, 1, Thunderclap, cardtable);
    card_create("True_Grit", "Gain 7 block. Exhaust a random card", TYPE_SKL, 0, 0, 1, True_Grit, cardtable);
    card_create("Inflame", "Gain 2 Strength.", TYPE_ABL, 0, 0, 1, Inflame, cardtable);

    card_create("TwinStrike", "Deal 5 damage twice.", TYPE_ATK, 5, 0, 1, TwinStrike, cardtable);
    card_create("Warcry", "Draw 1 card.", TYPE_SKL, 0, 1, 0, Warcry, cardtable);
    card_create("WildStrike", "Deal 12 damage.", TYPE_ATK, 12, 0, 1, WildStrike, cardtable);
    card_create("BattleTrance", "Draw 3 cards.", TYPE_SKL, 0, 0, 0, BattleTrance, cardtable);
    card_create("BloodforBlood", "Deal 18 damage.", TYPE_ATK, 18, 0, 4, BloodforBlood, cardtable);
    card_create("Bloodletting", "Lose 3 HP,Gain 2 Energy.", TYPE_SKL, 0, 0, 0, Bloodletting, cardtable);
    card_create("BurningPact", "Draw 2 cards.", TYPE_SKL, 0, 0, 1, BurningPact, cardtable);
    card_create("Carnage", "Deal 20 damage.", TYPE_ATK, 20, 0, 2, Carnage, cardtable);
    card_create("Combust", "lose 1 HP and deal 5 damage to ALL enemies.", TYPE_ABL, 5, 0, 1, Combust, cardtable);
    card_create("Disarm", "Enemy loses 2 Icon Strength.", TYPE_ABL, 0, 1, 1, Disarm, cardtable);
    card_create("Entrench", "Double your Block.", TYPE_SKL, 0, 0, 2, Entrench, cardtable);
    card_create("Evolve", "draw 1 card.", TYPE_ABL, 0, 0, 1, Evolve, cardtable);
    card_create("FeelNoPain", "gain 3  Block.", TYPE_ABL, 0, 0, 1, FeelNoPain, cardtable);
    card_create("GhostlyArmor", "Gain 10 Block.", TYPE_SKL, 0, 0, 1, GhostlyArmor, cardtable);
    card_create("Hemokinesis", "Lose 2 HP.Deal 15 damage.", TYPE_ATK, 15, 0, 1, Hemokinesis, cardtable);

    card_create("InfernalBlade", "Add a random card cost 0.\nExhaust.", TYPE_SKL, 0, 1, 1, InfernalBlade, cardtable);
    card_create("Inflame", "Gain 2 strength", TYPE_STRENGTH, 0, 0, 1, Inflame, cardtable);
    card_create("Intimidate", "Apply 1 Weak to ALL enemies.\nExhaust.", TYPE_SKL, 0, 1, 0, Intimidate, cardtable);
    card_create("Metallicize", "At the end of your turn, gain 3 Block.", TYPE_ABL, 0, 0, 1, Metallicize, cardtable);
    // card_create("PowerThrough", "Add 2 Wounds to your hand. Gain 15 Block.", PowerThrough, false, TYPE_SKL, &table);
    card_create("Pummel", "Deal 2 damage 4 times.\nExhaust.", TYPE_ATK, 2, 1, 1, Pummel, cardtable);
    card_create("Rage", "Whenever you play Attack this turn, gain 3 Block.", TYPE_SKL, 0, 0, 0, Rage, cardtable);
    card_create("Rampage", "Deal 8 damage. Increase this card's damage by 5.", TYPE_ATK, 8, 0, 1, Rampage, cardtable);
    // card_create("RecklessCharge", "Deal 7 damage. Shuffle a Dazed into your draw pile.", RecklessCharge, false, TYPE_ATK, &table);
    // card_create("Rupture", "Whenever you lose HP from a card, gain 1 Strength.", TYPE_ABL, 0, 0, 1, Rupture, cardtable);
    card_create("SearingBlow", "Deal 12 damage. Can be upgraded any number of times.", TYPE_ATK, 12, 0, 2, SearingBlow, cardtable);
    // card_create("SecondWind", "Exhaust all non-Attack cards in your hand and gain 5 Block for each card Exhausted.", TYPE_SKL, 0, 0, 1, SecondWind, cardtable);
    card_create("SeeingRed", "Gain 2 energy.\nExhaust.", TYPE_SKL, 0, 1, 1, SeeingRed, cardtable);
    card_create("Sentinel", "Gain 5 Block. If this card is Exhausted, gain 2 energy.", TYPE_SKL, 0, 0, 1, Sentinel, cardtable);
    card_create("SeverSoul", "Exhaust all non-Attack cards in your hand. Deal 16 damage.", TYPE_ATK, 16, 0, 2, SeverSoul, cardtable);
    card_create("ShockWave", "Apply 3 Weak and Icon Vulnerable Vulnerable to ALL enemies.\nExhaust.", TYPE_SKL, 0, 1, 2, ShockWave, cardtable);
    card_create("Uppercut", "Deal 13 damage. Apply 1 Weak. Apply 1 Vulnerable.", TYPE_ATK, 13, 0, 2, Uppercut, cardtable);
    card_create("Whirlwind", "Deal 5 damage to ALL enemies X times.", TYPE_ATK, 5, 0, 0, Whirlwind, cardtable);

    /* create enemy cards */

    card_create("DarkStrike", "None.", TYPE_ATK, 6, 0, 0, DarkStrike, cardtable);
    card_create("Incantation", "None.", TYPE_SKL, 0, 0, 0, Incantation, cardtable);

    /* create buff */
    DEBUG
    buff_create("Weak", "Weak creatures deal 25%% less damage with Attacks.", Buff_Weak, bufftable);

    buff_create("Vulnerable", "Target takes 50%% more damage from attacks.", Buff_Vulnerable, bufftable);
    buff_create("Ritual", "At the end of its turn, gains X Strength.", Buff_Ritual, bufftable);
    buff_create("Strength", "Increases attack damage by X (per hit).", Buff_Strength, bufftable);
    buff_create("Block", "Block is the amount of attack damage a character can take before the damage affects their HP.", Buff_Block, bufftable);

    /* create enemy */

    CardDeck deck;
    BuffDeck buff;
    card_deck_initialize(&deck);
    buff_deck_initialize(&buff);

    add_card_into_deck(&deck, "DarkStrike");
    add_card_into_deck(&deck, "Incantation");

    enemy_create("Cultist", Cultist, 50, 0, 50,&deck, &buff, enemytable);
    //Mouse
    card_deck_initialize(&deck);
    buff_deck_initialize(&buff);

    add_card_into_deck(&deck, "Chomp");
    add_card_into_deck(&deck, "Thrash");
    add_card_into_deck(&deck, "Bellow");

    enemy_create("Mouse", Mouse, 40, 0, 40,&deck, &buff, enemytable);
    //Lagavulin
    card_deck_initialize(&deck);
    buff_deck_initialize(&buff);

    add_card_into_deck(&deck, "LagavulinAttack");
    add_card_into_deck(&deck, "SiphonSoul");

    enemy_create("Lagavulin", Lagavulin, 100, 8, 100,&deck, &buff, enemytable);
}

void game_initialize(Game *game, Card *card, Player *player, Enemy *enemy, Field *field, CardTable *cardtable, BuffTable *bufftable, EnemyTable *enemytable)
{
    basic_card_add(player);
    game->card = card;
    game->player = player;
    game->enemy = enemy;
    game->field = field;
    game->cardtable = cardtable;
    game->bufftable = bufftable;
    game->enemytable = enemytable;
}

void basic_card_add(Player *player)
{
    for (int i = 0; i < 6; i++)
        add_card_into_deck(&(player->deck.deckCard), "Strike");
    for (int i = 0; i < 6; i++)
        add_card_into_deck(&(player->deck.deckCard), "Defend");
    add_card_into_deck(&(player->deck.deckCard), "Bash");
    add_card_into_deck(&(player->deck.deckCard), "Inflame");
}

char *random_enemy_name(EnemyTable *enemytable)
{
    int idx = rand() % enemytable->size;
    return enemytable->data[idx].name;
}

void round_start(Game *game)
{
    for (int i = 0; i < 5; i++)
        draw_card_random(&(game->player->deck));
    GtkComboBoxText *ComboBox = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(game->builder, "HandCardChooseBox"));
    Player *player = game->player;
    for (int i = 0; i < game->player->deck.handCard.size; i++)
    {
        char name[MAX_DESCRIPTION_LENGTH + 1];
        memset(name, 0, sizeof(name));
        strcat(name, player->deck.drawCard.card[i].name);
        strcat(name, ": ");
        strcat(name, player->deck.drawCard.card[i].description);
        gtk_combo_box_text_append_text(ComboBox, name);
    }
}

void hp_update(Game *game)
{
    GtkProgressBar *player_hp = GTK_PROGRESS_BAR(gtk_builder_get_object(game->builder, "PlayerHpBar"));
    GtkProgressBar *enemy_hp = GTK_PROGRESS_BAR(gtk_builder_get_object(game->builder, "EnemyHpBar"));
    double current = game->player->hp;
    double total = game->player->max_hp;
    char text[100];
    sprintf(text, "%.0f/%.0f", current, total); // 创建表示当前进度的字符串
    gtk_progress_bar_set_text(player_hp, text);
    current = game->enemy->hp;
    current = game->enemy->max_hp;
    sprintf(text, "%.0f/%.0f", current, total);
    gtk_progress_bar_set_fraction(enemy_hp, current / total); // 计算并设置进度
}

void clear_box(GtkWidget *box)
{
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(box));
    for (iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);
}

void buff_update(Game *game)
{
    GtkBox *player_buff = GTK_BOX(gtk_builder_get_object(game->builder, "PlayerBuffBox"));
    GtkBox *enemy_buff = GTK_BOX(gtk_builder_get_obj(game->builder, "EnemyBuffBox"));
    clear_box(GTK_WIDGET(player_buff));
    clear_box(GTK_WIDGET(enemy_buff));
    for (int i = 0; i < game->player->buff.size; i++)
    {
        char name[MAX_DESCRIPTION_LENGTH + 1];
        sprintf(name, "%s: %s", game->player->buff.deck[i].name, game->player->buff.deck[i].level);
        GtkLabel *label = gtk_label_new(name);
        gtk_box_pack_start(player_buff, label, 0, 0, TRUE);
    }
    for (int i = 0; i < game->enemy->buff.size; i++)
    {
        char name[MAX_DESCRIPTION_LENGTH + 1];
        sprintf(name, "%s: %s", game->enemy->buff.deck[i].name, game->enemy->buff.deck[i].level);
        GtkLabel *label = gtk_label_new(name);
        gtk_box_pack_start(enemy_buff, label, 0, 0, TRUE);
    }
}