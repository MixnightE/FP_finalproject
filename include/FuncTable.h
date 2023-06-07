#ifndef _FUNC_TABLE_H_
#define _FUNC_TABLE_H_

#include <Player.h>
#include <Enemy.h>
#include <Field.h>
#include <Card.h>

typedef struct CardMapData
{
    char *name;
    void (*fp)(Card *, Player *, Enemy *, Field *);
} CardMap;

typedef struct CardTableData
{
    int size;
    CardMap data[MAX_CARD_NUM];
} CardTable;

typedef struct EnemyMapData
{
    char *name;
    void (*fp)(Card *, Player *, Enemy *, Field *, CardTable *);
} EnemyMap;

typedef struct EnemyTableData
{
    int size;
    EnemyMap data[MAX_CARD_NUM];
} EnemyTable;

/* funtion table functions defination */

/**
 * @brief 初始化CardTable
 */
void card_table_initialize(CardTable *table);

/**
 * @brief 新增對應關係至table中
 */
void card_table_add(CardTable *table, char *name, void (*fp)(Card *, Player *, Enemy *, Field *));

/**
 * @brief 以table為映射表，找到對應於name的function pointer
 * @return 如果找到則回傳function pointer，如果沒找到則回傳NULL
 */
void *card_table_transform(CardTable *table, const char *name);

/**
 * @brief 初始化EnemyTable
 */
void enemy_table_initialize(EnemyTable *table);

/**
 * @brief 新增對應關係至table中
 */
void enemy_table_add(EnemyTable *table, char *name, void (*fp)(Card *, Player *, Enemy *, Field *, CardTable *));

/**
 * @brief 以table為映射表，找到對應於name的function pointer
 * @return 如果找到則回傳function pointer，如果沒找到則回傳NULL
 */
void *enemy_table_transform(EnemyTable *table, const char *name);

#endif // _FUNC_TABLE_H_