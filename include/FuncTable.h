#ifndef _FUNC_TABLE_H_
#define _FUNC_TABLE_H_

#include <Constant.h>
#include <Player.h>
#include <Enemy.h>
#include <Field.h>

typedef struct FuncMapData
{
    char *name;
    void (*fp)(Player *, Enemy *, Field *);
} FuncMap;

typedef struct FuncTableData
{
    int size;
    FuncMap data[MAX_CARD_NUM];
} FuncTable;

/**
 * @brief 初始化FuncTable
 */
void function_table_initialize(FuncTable *ftable);

/**
 * @brief 新增對應關係至ftable中
 */
void func_table_add(FuncTable *ftable, char *name, void (*fp)(Player *, Enemy *, Field *));

/**
 * @brief 以ftable為映射表，找到對應於name的function pointer
 * @return 如果找到則回傳function pointer，如果沒找到則回傳NULL
 */
void *name_to_function_pointer(FuncTable *ftable, const char *name);

#endif // _FUNC_TABLE_H_