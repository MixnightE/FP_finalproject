#include <Battle.h>
#include <cJSON.h>
#include <fileIO.h>

void call_enemy(Enemy *enemy, char *name)
{
    cJSON *json = cJSON_Read("./data/enemy.json");
    cJSON *enemy_data = cJSON_GetObjectItem(json, name);
    enemy->name = name;
    enemy->hp = cJSON_GetObjectItem(enemy_data, "hp")->valueint;
    enemy->def = cJSON_GetObjectItem(enemy_data, "def")->valueint;
    cJSON *card_deck = cJSON_GetObjectItem(enemy_data, "deck");
    for (int i = 0; i < cJSON_GetArraySize(card_deck); i++)
    {
        char *card_name = cJSON_GetArrayItem(card_deck, i)->valuestring;
        add_card_into_deck(&(enemy->deck), card_name);
    }
    cJSON *buff = cJSON_GetObjectItem(enemy_data, "buff");
    buff_deck_initialize(&(enemy->buff));
    if (buff != NULL && cJSON_IsObject(buff))
    {
        cJSON *item = buff->child;
        while (item != NULL)
        {
            if (cJSON_IsNumber(item))
            {
                enemy->buff.deck[enemy->buff.size].name = item->string;
                enemy->buff.deck[enemy->buff.size].level = item->valueint;
                enemy->buff.size++;
            }
            item = item->next;
        }
    }
    cJSON_Delete(json);
}

void Battle(Player *player, Enemy *enemy, Field *field, CardTable *cardtable)
{
    while (1)
    {

        player_new_round(player, enemy, field);

        // 抽卡
        for (int i = 0; i < 5; i++)
            draw_card_random(&(player->deck));

        while (player->energy > 0)
        {
            char choose_card[MAX_NAME_LENGTH + 1];
            scanf("choose card: %s", choose_card);
            player_choose_card(player, enemy, field, cardtable, choose_card);
        }

        enemy_new_round(player, enemy, field);

        char name[MAX_NAME_LENGTH + 1];
        scanf("choose card: %s", name);
    }
}