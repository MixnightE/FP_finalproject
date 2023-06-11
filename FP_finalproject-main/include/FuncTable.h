#ifndef _FUNC_TABLE_H_
#define _FUNC_TABLE_H_

#include <Player.h>
#include <Enemy.h>
#include <Field.h>
#include <Card.h>

typedef void (*BuffFunction)(Card *, Player *, Enemy *, Field *);
typedef void (*CardFunction)(Card *, Player *, Enemy *, Field *);

typedef struct CardMapData
{
    char *name;
    CardFunction fp;
} CardMap;

typedef struct CardTableData
{
    int size;
    CardMap data[MAX_CARD_NUM];
} CardTable;

typedef void (*EnemyFunction)(Player *, Enemy *, Field *, CardTable *);

typedef struct EnemyMapData
{
    char *name;
    EnemyFunction fp;
} EnemyMap;

typedef struct EnemyTableData
{
    int size;
    EnemyMap data[MAX_CARD_NUM];
} EnemyTable;

typedef struct BuffMapData
{
    char *name;
    BuffFunction fp;
} BuffMap;

typedef struct BuffTableData
{
    int size;
    BuffMap data[MAX_CARD_NUM];
} BuffTable;

/* funtion table functions defination */

/**
 * @brief 初始化CardTable
 */
void card_table_initialize(CardTable *table);

/**
 * @brief 新增對應關係至table中
 */
void card_table_add(CardTable *table, char *name, CardFunction fp);

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
void enemy_table_add(EnemyTable *table, char *name, EnemyFunction fp);

/**
 * @brief 以table為映射表，找到對應於name的function pointer
 * @return 如果找到則回傳function pointer，如果沒找到則回傳NULL
 */
void *enemy_table_transform(EnemyTable *table, const char *name);

/**
 * @brief 初始化EnemyTable
 */
void buff_table_initialize(BuffTable *table);

/**
 * @brief 新增對應關係至table中
 */
void buff_table_add(BuffTable *table, char *name, BuffFunction fp);

/**
 * @brief 以table為映射表，找到對應於name的function pointer
 * @return 如果找到則回傳function pointer，如果沒找到則回傳NULL
 */
void *buff_table_transform(BuffTable *table, const char *name);

#endif // _FUNC_TABLE_H_