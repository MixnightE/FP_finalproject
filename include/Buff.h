#ifndef _BUFF_H_
#define _BUFF_H_

#include <Constant.h>
#include <head.h>

typedef enum BuffType
{
    TYPE_MULTISHIELD, // 多重護甲
    TYPE_POISON,      // 中毒
    TYPE_WEAK,        // 虛弱
    TYPE_VULNERABLE,  // 易傷
} BuffType;

typedef struct BuffData
{
    char *name;
    char *description;
    int level;
    BuffType type;
} Buff;

typedef struct BuffDeckData
{
    int size;
    Buff deck[MAX_DECK_SIZE];
} BuffDeck;

/* Buff functions definations */

/**
 * @brief 初始化BuffDeck結構
 */
void buff_deck_initialize(BuffDeck *buff);

/**
 * @brief 在buff列表中尋找名為name的buff
 * @return 在Deck中的位置，未找到則回傳-1
 */
int find_buff_from_deck(BuffDeck *deck, const char *name);

/**
 * @brief 將buff2的屬性賦予buff1
 */
void buff_assign(Buff *buff1, Buff *buff2);

/**
 * @brief 在BuffDeck中加入Buff
 */
void add_buff_into_deck(BuffDeck *deck, const char *buffname, int level);

/**
 * @brief 將buff從json中導出
 */
Buff *import_buff_from_json(const char *buffname);

#endif // _BUFF_H_