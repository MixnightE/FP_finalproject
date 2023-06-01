#include <Enemy.h>
#include <Player.h>
#include <Field.h>
#include <FuncTable.h>
#include <cJSON.h>
#include <head.h>

void enemy_create(const char *name, const char *description, char *func_name, void (*function)(Player *, Enemy *, Field *), FuncTable *ftable)
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
        ftable->data[ftable->size].name = func_name;
        ftable->data[ftable->size].fp = function;
        ftable->size++;
        cJSON_AddStringToObject(new_obj, "name", name);
        cJSON_AddStringToObject(new_obj, "description", description);
        cJSON_AddStringToObject(new_obj, "function", (const char *const)func_name);
        cJSON_AddItemToObject(json, name, new_obj);
        cJSON_Write("./data/enemy.json", json);
    }
    cJSON_Delete(json);
}