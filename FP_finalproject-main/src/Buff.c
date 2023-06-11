#include <Buff.h>
#include <cJSON.h>
#include <fileIO.h>

void buff_deck_initialize(BuffDeck *buff)
{
    buff->size = 0;
}

int find_buff_from_deck(BuffDeck *deck, const char *name)
{
    for (int i = 0; i < deck->size; i++)
    {
        if (!strcmp(name, deck->deck[i].name))
            return i;
    }
    return -1;
}

void buff_assign(Buff *buff1, Buff *buff2)
{
    buff1->description = buff1->description;
    buff1->level = buff2->level;
    buff1->name = buff2->name;
    buff1->type = buff2->type;
}

void add_buff_into_deck(BuffDeck *deck, const char *buffname, int level)
{
    int idx;
    if ((idx = find_buff_from_deck(deck, buffname)) == -1)
    {
        Buff *buff = import_buff_from_json(buffname);

        // fprintf(stderr, "Buff Debug: %s: %d\n", buff->name, buff->level);
        buff_assign(deck->deck + deck->size, buff);
        free(buff);
        idx = deck->size;
        deck->size++;
    }
    deck->deck[idx].level += level;
    // fprintf(stderr, "Buff Debug: %s: %d\n", deck->deck[idx].name, deck->deck[idx].level);
}

Buff *import_buff_from_json(const char *buffname)
{
    cJSON *json = cJSON_Read("./data/buff.json");
    if (!cJSON_HasObjectItem(json, buffname))
    {
        fprintf(stderr, "Import Buff From Json Error: Don't have the item: %s.\n", buffname);
        exit(1);
    }
    cJSON *buff_data = cJSON_GetObjectItem(json, buffname);
    Buff *buff = (Buff *)malloc(sizeof(Buff));
    buff->name = cJSON_GetObjectItem(buff_data, "name")->valuestring;
    // fprintf(stderr, "name: %s\n", buff->name);
    buff->description = cJSON_GetObjectItem(buff_data, "description")->valuestring;
    // cJSON_Delete(json);
    return buff;
}

void remove_buff_from_deck(BuffDeck *buff, const char *name)
{
    int idx;
    if ((idx = find_buff_from_deck(buff, name)) != -1)
    {
        for (int i = idx + 1; i < buff->size; i++)
        {
            buff_assign(&(buff->deck[i - 1]), &(buff->deck[i]));
        }
    }
}