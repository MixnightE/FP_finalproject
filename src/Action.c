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
    }
    else if (card->type == TYPE_SKL)
    {
        int idx;
        if ((idx = find_buff_from_deck(&(player->buff), "Defense")) != -1)
            Buff_Defense(card, player, NULL, NULL);
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
    void (*function)(Card *, Player *, Enemy *, Field *) = card_table_transform(table, name);
    function(&card, player, enemy, field);
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
    if ((idx = card_find(&(enemy->deck), name)) != -1)
    {
        card_assign(&card, &(enemy->deck.card[idx]));
    }
    // Buff結算
    enemy_buff_action(&card, player, enemy, field);
    // CardAction
    void (*function)(Card *, Player *, Enemy *, Field *) = card_table_transform(table, name);
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
    if ((idx = find_buff_from_deck(&(enemy->buff), "Defense")) != -1)
        enemy->buff.deck[idx].level = 0;
    player->def = 0;

    if (player->hp <= 0 || enemy->hp <= 0)
    {
        battle_over(player, enemy, field);
    }
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

    if (player->hp <= 0 || enemy->hp <= 0)
    {
        battle_over(player, enemy, field);
    }
}

void card_create(char *name, const char *description, void (*function)(Card *, Player *, Enemy *, Field *), int type, CardTable *table)
{
    cJSON *json = cJSON_Read("./data/card.json");
    cJSON *new_obj = cJSON_CreateObject();
    if (new_obj == NULL)
    {
        fprintf(stderr, "Card Create Error: Create object failed.\n");
        exit(1);
    }
    if (!cJSON_HasObjectItem(json, name))
    {
        card_table_add(table, name, function);
        cJSON_AddStringToObject(new_obj, "name", name);
        cJSON_AddStringToObject(new_obj, "description", description);
        cJSON_AddNumberToObject(new_obj, "type", type);
        cJSON_AddItemToObject(json, name, new_obj);
        cJSON_Write("./data/card.json", json);
    }
    cJSON_Delete(json);
}

void enemy_create(char *name, void (*function)(Card *, Player *, Enemy *, Field *, CardTable *), int hp, int def, CardDeck *deck, BuffDeck *buff, EnemyTable *table)
{
    cJSON *json = cJSON_Read("./data/enemy.json");
    cJSON *new_obj = cJSON_CreateObject();
    if (new_obj == NULL)
    {
        fprintf(stderr, "Enemy Create Error: Create object failed.\n");
        exit(1);
    }
    if (!cJSON_HasObjectItem(json, name))
    {
        enemy_table_add(table, name, function);
        cJSON_AddStringToObject(new_obj, "name", name);
        cJSON_AddNumberToObject(new_obj, "hp", hp);
        cJSON_AddNumberToObject(new_obj, "def", def);
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
        cJSON_AddItemToObject(json, name, new_obj);
        cJSON_Write("./data/enemy.json", json);
    }
    cJSON_Delete(json);
}

void card_deck_add(CardPile *cardPile, CardTable *mappingTable, const char *name)
{
    cJSON *json = cJSON_Read("./data/card.json");
    cJSON *card_data = cJSON_GetObjectItemCaseSensitive(json, name);
    cardPile->deckCard.card[cardPile->deckCard.size].name = cJSON_GetObjectItemCaseSensitive(card_data, "name")->valuestring;
    cardPile->deckCard.card[cardPile->deckCard.size].description = cJSON_GetObjectItemCaseSensitive(card_data, "description")->valuestring;
    cardPile->deckCard.card[cardPile->deckCard.size].isUpdated = cJSON_GetObjectItemCaseSensitive(card_data, "isUpdated")->type;
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