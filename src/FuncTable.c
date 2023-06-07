#include <FuncTable.h>

void card_table_initialize(CardTable *table)
{
    table->size = 0;
}

void enemy_table_initialize(EnemyTable *table)
{
    table->size = 0;
}

void card_table_add(CardTable *table, char *name, void (*fp)(Card *, Player *, Enemy *, Field *))
{
    table->data[table->size].fp = fp;
    table->data[table->size].name = name;
    table->size++;
}

void enemy_table_add(EnemyTable *table, char *name, void (*fp)(Card *, Player *, Enemy *, Field *, CardTable *))
{
    table->data[table->size].fp = fp;
    table->data[table->size].name = name;
    table->size++;
}

void *card_table_transform(CardTable *table, const char *name)
{
    for (int i = 0; i < table->size; i++)
    {
        if (!strcmp(table->data[i].name, name))
            return table->data[i].fp;
    }
    return NULL;
}

void *enemy_table_transform(EnemyTable *table, const char *name)
{
    for (int i = 0; i < table->size; i++)
    {
        if (!strcmp(table->data[i].name, name))
            return table->data[i].fp;
    }
    return NULL;
}