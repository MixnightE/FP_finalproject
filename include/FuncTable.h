#ifndef _FUNC_TABLE_H_
#define _FUNC_TABLE_H_

#include <Constant.h>

typedef struct FuncMapData
{
    char *name;
    void(*fp);
} FuncMap;

typedef struct FuncTableData
{
    int size;
    FuncMap data[MAX_CARD_NUM];
} FuncTable;

/**
 * @brief 初始化FuncTable
 */
void func_table_initialize(FuncTable *ftable);

/**
 * @brief 以ftable為映射表，找到對應於name的function pointer
 * @return 如果找到則回傳function pointer，如果沒找到則回傳NULL
 */
void *name_to_function_pointer(FuncTable *ftable, const char *name);

/**
 * @brief 創造卡片
 */
void card_create(const char *name, const char *description, const char *func_name);

/**
 * @brief 將卡片轉為名為name的卡片
 * @return 如果成功回傳卡片指針，失敗回傳NULL
 */
Card *card_init(Card *card, FuncTable *mappingTable, const char *name);

#endif // _FUNC_TABLE_H_