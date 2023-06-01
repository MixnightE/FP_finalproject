#include <FuncTable.h>
#include <fileIO.h>
#include <head.h>
#include <Player.h>
#include <Field.h>
#include <Enemy.h>

void function_table_initialize(FuncTable *ftable)
{
    ftable->size = 0;
}

void func_table_add(FuncTable *ftable, const char *name, void(*fp))
{
    ftable->data[ftable->size - 1].fp = fp;
    ftable->data[ftable->size - 1].name = name;
    ftable->size++;
}

void *name_to_function_pointer(FuncTable *ftable, const char *name)
{
    for (int i = 0; i < ftable->size; i++)
    {
        if (!strcpy(ftable->data[i].name, name))
            return ftable->data[i].fp;
    }
    return NULL;
}

void card_create(const char *name, const char *description, const char *func_name)
{
    cJSON *json = cJSON_Read("./card.json");
    cJSON *new_obj = cJSON_CreateObject();
    if (new_obj == NULL)
    {
        fprintf(stderr, "NermalAttack_create Error: Create object failed.\n");
        exit(1);
    }
    cJSON_AddStringToObject(new_obj, "name", name);
    cJSON_AddStringToObject(new_obj, "description", description);
    cJSON_AddStringToObject(new_obj, "function", func_name);
    cJSON_AddItemToObject(json, name, new_obj);
    cJSON_Write("./card.json", json);
}

Card *card_init(Card *card, FuncTable *mappingTable, const char *name)
{
    cJSON *json = cJSON_Read("./card.json");
    cJSON *card_data = cJSON_GetObjectItemCaseSensitive(json, name);
    strcpy(card->name, cJSON_GetObjectItemCaseSensitive(card_data, "name")->valuestring);
    strcpy(card->description, cJSON_GetObjectItemCaseSensitive(card_data, "description")->valuestring);
    card->function = name_to_function_pointer(mappingTable, cJSON_GetObjectItemCaseSensitive(card_data, "function")->valuestring);
    if (card->function == NULL)
        return NULL;
    else
        return card;
}