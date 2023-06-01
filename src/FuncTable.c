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

void func_table_add(FuncTable *ftable, char *name, void (*fp)(Player *, Enemy *, Field *))
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