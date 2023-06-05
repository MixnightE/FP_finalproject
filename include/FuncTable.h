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

/**
 * @brief 創造卡片
 */
void card_create(const char *name, const char *description, void (*function)(Card *, Player *, Enemy *, Field *), bool isUpdated, int type, FuncTable *ftable);
/**
 * @brief 將卡片轉為名為name的卡片
 * @return 如果成功回傳卡片指針，失敗回傳NULL
 */
void card_deck_add(CardPile *cardPile, FuncTable *mappingTable, const char *name);

#endif // _FUNC_TABLE_H_