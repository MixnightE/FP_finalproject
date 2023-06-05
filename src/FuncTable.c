#include <FuncTable.h>
#include <fileIO.h>
#include <head.h>
#include <Card.h>
#include <Player.h>
#include <Field.h>
#include <Enemy.h>

void function_table_initialize(FuncTable *ftable)
{
    ftable->size = 0;
}

void func_table_add(FuncTable *ftable, char *name, void (*fp)(Card *, Player *, Enemy *, Field *))
{
    ftable->data[ftable->size - 1].fp = fp;
    ftable->data[ftable->size - 1].name = name;
    ftable->size++;
}

void *name_to_function_pointer(FuncTable *ftable, const char *name)
{
    for (int i = 0; i < ftable->size; i++)
    {
        if (!strcmp(ftable->data[i].name, name))
            return ftable->data[i].fp;
    }
    return NULL;
}

void card_create(const char *name, const char *description, bool isUpdated, int type, FuncTable *ftable)
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
        cJSON_AddStringToObject(new_obj, "name", name);
        cJSON_AddStringToObject(new_obj, "description", description);
        cJSON_AddBoolToObject(new_obj, "isUpdated", isUpdated);
        cJSON_AddNumberToObject(new_obj, "type", type);
        cJSON_AddItemToObject(json, name, new_obj);
        cJSON_Write("./data/card.json", json);
    }
    cJSON_Delete(json);
}

void card_deck_add(CardPile *cardPile, FuncTable *mappingTable, const char *name)
{
    cJSON *json = cJSON_Read("./data/card.json");
    cJSON *card_data = cJSON_GetObjectItemCaseSensitive(json, name);
    cardPile->deckCard.card[cardPile->deckCard.size].name = cJSON_GetObjectItemCaseSensitive(card_data, "name")->valuestring;
    cardPile->deckCard.card[cardPile->deckCard.size].description = cJSON_GetObjectItemCaseSensitive(card_data, "description")->valuestring;
    cardPile->deckCard.card[cardPile->deckCard.size].isUpdated = cJSON_GetObjectItemCaseSensitive(card_data, "isUpdated")->type;
    cardPile->deckCard.card[cardPile->deckCard.size].type = cJSON_GetObjectItemCaseSensitive(card_data, "type")->valuedouble;
    cardPile->deckCard.size++;
}