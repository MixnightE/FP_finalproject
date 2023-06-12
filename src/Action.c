#include <Action.h>

void player_buff_action(Card *card, Player *player, Enemy *enemy, Field *field)
{
    if (card->type == TYPE_ATK)
    {
        int idx;
        if ((idx = find_buff_from_deck(&(enemy->buff), "Vulnerable")) != -1)
            Buff_Vulnerable(card, NULL, NULL, NULL);
        if ((idx = find_buff_from_deck(&(player->buff), "Weak")) != -1)
            Buff_Weak(card, NULL, NULL, NULL);
        if ((idx = find_buff_from_deck(&(player->buff), "Strength")) != -1)
            Buff_Strength(card, player, NULL, NULL);
        if ((idx = find_buff_from_deck(&(player->buff), "Rage")) != -1)
            Buff_Rage(NULL, player, NULL, NULL);
    }
    else if (card->type == TYPE_SKL)
    {
        int idx;
        if ((idx = find_buff_from_deck(&(player->buff), "Block")) != -1)
            Buff_Block(card, player, NULL, NULL);
    }
    else
    {
    }
}

void enemy_buff_action(Card *card, Player *player, Enemy *enemy, Field *field)
{
    if (card->type == TYPE_ATK)
    {
        int idx;
        if ((idx = find_buff_from_deck(&(player->buff), "Vulnerable")) != -1)
            Buff_Vulnerable(card, NULL, NULL, NULL);
        if ((idx = find_buff_from_deck(&(enemy->buff), "Weak")) != -1)
            Buff_Weak(card, NULL, NULL, NULL);
        if ((idx = find_buff_from_deck(&(enemy->buff), "Strength")) != -1)
            Buff_Strength(card, NULL, enemy, NULL);
    }
    else if (card->type == TYPE_SKL)
    {
    }
    else
    {
    }
}

void player_choose_card(Player *player, Enemy *enemy, Field *field, CardTable *table, const char *name)
{
    if (player->hp <= 0 || enemy->hp <= 0)
    {
        battle_over(player, enemy, field);
    }
    // 選卡
    int idx;
    Card card;
    if ((idx = card_find(&(player->deck.handCard), name)) != -1)
    {
        card_assign(&card, &(player->deck.handCard.card[idx]));
    }

    // Buff結算
    player_buff_action(&card, player, enemy, field);
    // CardAction
    CardFunction function = card_table_transform(table, name);
    if (player->energy >= card.energy)
    {
        player->energy -= card.energy;
        function(&card, player, enemy, field);
    }
    else
    {
        fprintf(stdout, "Out of energy.\n");
        return;
    }
    if (card.isExhaust)
        card_remove(&(player->deck.handCard), name);
    else
        fold_card(&(player->deck), name);
}

void enemy_choose_card(Player *player, Enemy *enemy, Field *field, CardTable *table, const char *name)
{
    if (player->hp <= 0 || enemy->hp <= 0)
    {
        battle_over(player, enemy, field);
    }
    // 選卡
    int idx;
    Card card;
    // Buff結算
    enemy_buff_action(&card, player, enemy, field);
    // CardAction
    CardFunction function = (CardFunction)card_table_transform(table, name);
    function(&card, player, enemy, field);
}

void player_new_round(Player *player, Enemy *enemy, Field *field)
{
    // 回合開始卡
    int idx;
    if ((idx = find_buff_from_deck(&(enemy->buff), "Weak")) != -1)
        enemy->buff.deck[idx].level--;
    if ((idx = find_buff_from_deck(&(player->buff), "Poison")) != -1)
        player->hp -= player->buff.deck[idx].level--;
    if ((idx = find_buff_from_deck(&(enemy->buff), "Vulnerable")) != -1)
        enemy->buff.deck[idx].level--;
    if ((idx = find_buff_from_deck(&(enemy->buff), "Block")) != -1)
        enemy->buff.deck[idx].level = 0;
    if (player->energy < 3)
        player->energy = 3;
    if (player->hp <= 0 || enemy->hp <= 0)
        battle_over(player, enemy, field);
}

void enemy_new_round(Player *player, Enemy *enemy, Field *field)
{
    // 回合開始卡
    int idx;
    if ((idx = find_buff_from_deck(&(player->buff), "Weak")) != -1)
        player->buff.deck[idx].level--;
    if ((idx = find_buff_from_deck(&(enemy->buff), "Poison")) != -1)
        enemy->hp -= enemy->buff.deck[idx].level--;
    if ((idx = find_buff_from_deck(&(player->buff), "Vulnerable")) != -1)
        player->buff.deck[idx].level--;
    if ((idx = find_buff_from_deck(&(enemy->buff), "Ritual")) != -1)
        Buff_Ritual(NULL, NULL, enemy, field);
    if ((idx = find_buff_from_deck(&(player->buff), "Rage")) != -1)
        remove_buff_from_deck(&(player->buff), "Rage");

    if (player->hp <= 0 || enemy->hp <= 0)
    {
        battle_over(player, enemy, field);
    }
}

void card_create(char *name, const char *description, int type, int atk, bool isExhaust, int energy, CardFunction function, CardTable *table)
{
    Card *card;
    cJSON *json = cJSON_Read("./data/card.json");
    cJSON *new_obj = cJSON_CreateObject();
    if (new_obj == NULL)
    {
        fprintf(stderr, "Card Create Error: Create object failed.\n");
        exit(1);
    }
    card_table_add(table, name, function);
    cJSON_AddStringToObject(new_obj, "name", name);
    cJSON_AddStringToObject(new_obj, "description", description);
    cJSON_AddNumberToObject(new_obj, "type", type);
    cJSON_AddNumberToObject(new_obj, "atk", atk);
    cJSON_AddBoolToObject(new_obj, "isExhaust", false);
    cJSON_AddNumberToObject(new_obj, "energy", energy);
    if (!cJSON_HasObjectItem(json, name))
        cJSON_AddItemToObject(json, name, new_obj);
    else
        cJSON_ReplaceItemInObject(json, name, new_obj);
    cJSON_Write("./data/card.json", json);
    cJSON_Delete(json);
}

void enemy_create(char *name, EnemyFunction function, int hp, int def, int max_hp, CardDeck *deck, BuffDeck *buff, EnemyTable *table)
{
    cJSON *json = cJSON_Read("./data/enemy.json");
    cJSON *new_obj = cJSON_CreateObject();
    if (new_obj == NULL)
    {
        fprintf(stderr, "Enemy Create Error: Create object failed.\n");
        exit(1);
    }
    enemy_table_add(table, name, function);
    cJSON_AddStringToObject(new_obj, "name", name);
    cJSON_AddNumberToObject(new_obj, "hp", hp);
    cJSON_AddNumberToObject(new_obj, "def", def);
    cJSON_AddNumberToObject(new_obj, "max_hp", max_hp);
    cJSON *new_arr = cJSON_CreateArray();
    if (new_arr == NULL)
    {
        fprintf(stderr, "Enemy Create Error: Create array failed.\n");
        exit(1);
    }
    for (int i = 0; i < deck->size; i++)
    {
        cJSON *string = cJSON_CreateString(deck->card[i].name);
        cJSON_AddItemToArray(new_arr, string);
    }
    cJSON_AddItemToObject(new_obj, "deck", new_arr);
    cJSON *new_buff_obj = cJSON_CreateObject();
    if (new_buff_obj == NULL)
    {
        fprintf(stderr, "Enemy Create Error: Create object failed.\n");
        exit(1);
    }
    for (int i = 0; i < buff->size; i++)
    {
        cJSON_AddNumberToObject(new_buff_obj, buff->deck[i].name, buff->deck[i].level);
    }
    cJSON_AddItemToObject(new_obj, "buff", new_buff_obj);

    if (!cJSON_HasObjectItem(json, name))
        cJSON_AddItemToObject(json, name, new_obj);
    else
        cJSON_ReplaceItemInObject(json, name, new_obj);
    cJSON_Write("./data/enemy.json", json);
    cJSON_Delete(json);
}

void buff_create(char *name, const char *description, BuffFunction function, BuffTable *table)
{
    Buff *buff;
    cJSON *json = cJSON_Read("./data/buff.json");
    cJSON *new_obj = cJSON_CreateObject();
    if (new_obj == NULL)
    {
        fprintf(stderr, "Buff Create Error: Create object failed.\n");
        exit(1);
    }
    buff_table_add(table, name, function);
    cJSON_AddStringToObject(new_obj, "name", name);
    cJSON_AddStringToObject(new_obj, "description", description);
    if (!cJSON_HasObjectItem(json, name))
        cJSON_AddItemToObject(json, name, new_obj);
    else
        cJSON_ReplaceItemInObject(json, name, new_obj);
    cJSON_Write("./data/buff.json", json);
    cJSON_Delete(json);
}

void card_deck_add(CardPile *cardPile, CardTable *mappingTable, const char *name)
{
    cJSON *json = cJSON_Read("./data/card.json");
    cJSON *card_data = cJSON_GetObjectItemCaseSensitive(json, name);
    cardPile->deckCard.card[cardPile->deckCard.size].name = cJSON_GetObjectItemCaseSensitive(card_data, "name")->valuestring;
    cardPile->deckCard.card[cardPile->deckCard.size].description = cJSON_GetObjectItemCaseSensitive(card_data, "description")->valuestring;
    cardPile->deckCard.card[cardPile->deckCard.size].isExhaust = cJSON_GetObjectItemCaseSensitive(card_data, "isExhaust")->type;
    cardPile->deckCard.card[cardPile->deckCard.size].type = cJSON_GetObjectItemCaseSensitive(card_data, "type")->valuedouble;
    cardPile->deckCard.size++;
}

void battle_over(Player *player, Enemy *enemy, Field *field)
{
    if (enemy->hp <= 0)
    {
        printf("You Win");
        printf("Select Next Level");
        exit(0);
        // 下一關
    }
    else
    {
        printf("Game over");
        exit(0);
        // 遊戲結束
    }
}

void print_battlefield(Player *player, Enemy *enemy, Field *field, char *extra_messages)
{
#ifdef __APPLE__
    system("clear");
#endif
#ifdef __linux__
    system("clear");
#endif
#ifdef __WIN32__
    system("cls");
#endif
    fprintf(stdout, "%s\t\t%s\t\t%s\n", "player", "field", "enemy");
    fprintf(stdout, "energy: %d\t\t\t%s\n", player->energy, enemy->name);
    fprintf(stdout, "hp: %d\t\tround: %d\thp: %d\n", player->hp, field->round, enemy->hp);
    fprintf(stdout, "def: %d\t\t\t\tdef: %d\n", player->def, enemy->def);
    print_player_buff(player);
    print_enemy_buff(enemy);
    fprintf(stdout, "%s\n", extra_messages);
    print_card_deck(&(player->deck.handCard));
}

void print_player_buff(Player *player)
{
    fprintf(stdout, "Player's Buff: \n");
    for (int i = 0; i < player->buff.size; i++)
    {
        fprintf(stdout, "%s: %d\n", player->buff.deck[i].name, player->buff.deck[i].level);
    }
}

void print_enemy_buff(Enemy *enemy)
{
    fprintf(stdout, "Enemy's Buff: \n");
    for (int i = 0; i < enemy->buff.size; i++)
    {
        fprintf(stdout, "%s: %d\n", enemy->buff.deck[i].name, enemy->buff.deck[i].level);
    }
}