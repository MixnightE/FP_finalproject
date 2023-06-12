#include <Battle.h>
#include <cJSON.h>
#include <fileIO.h>

void call_enemy(Enemy *enemy, char *name)
{
    cJSON *json = cJSON_Read("./data/enemy.json");
    cJSON *enemy_data = cJSON_GetObjectItem(json, name);
    enemy->name = name;
    enemy->hp = cJSON_GetObjectItem(enemy_data, "hp")->valueint;
    enemy->max_hp = cJSON_GetObjectItem(enemy_data, "hp")->valueint;
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

void Battle(Player *player, Enemy *enemy, Field *field, CardTable *cardtable, EnemyTable *enemytable, BuffTable *bufftable)
{
    FILE *fp;
    field->round = 1;
    char command[MAX_NAME_LENGTH + 1];
    char buffer[MAX_DESCRIPTION_LENGTH + 1];
    char message[(MAX_DESCRIPTION_LENGTH + 1) * MAX_NAME_LENGTH];
    while (1)
    {

        player_new_round(player, enemy, field);

        put_card(&(player->deck));
        // 抽卡
        for (int i = 0; i < 5; i++)
            draw_card_random(&(player->deck));

        while (1)
        {
            print_battlefield(player, enemy, field, "");
            fprintf(stdout, "command: ");
            fscanf(stdin, "%s", command);
            if (!strcmp(command, "End"))
                break;
            player_choose_card(player, enemy, field, cardtable, command);
        }
        print_battlefield(player, enemy, field, "");
        drop_card(&(player->deck));
        fp = fopen("./data/message.txt", "w");
        fclose(fp);
        enemy_new_round(player, enemy, field);
        EnemyFunction function = enemy_table_transform(enemytable, enemy->name);
        function(player, enemy, field, cardtable);
        fp = fopen("./data/message.txt", "r");
        while (fgets(buffer, MAX_DESCRIPTION_LENGTH, fp))
            strcat(message, buffer);
        fclose(fp);
        print_battlefield(player, enemy, field, message);
        fprintf(stdout, "command: ");
        fscanf(stdin, "%s", command);
        if (strcmp(command, "NewRound"))
            print_battlefield(player, enemy, field, message);
        field->round++;
    }
}