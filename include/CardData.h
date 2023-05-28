#ifndef _CARD_H_
#define _CARD_H_

#include <Constant.h>

typedef struct cardDataType
{
    char name[MAX_CARD_NAME_LENGTH + 1];
    int id; // 卡片編號
} CardData;

typedef struct cardPool
{
    // 使用並查集

    int size;
    int capacity;
    int *cards;
} CardPool;

/**
 * @brief 新增卡片進卡池
 * @param card_pool 卡池
 * @param card 要新增的卡片
 */
void CardPoolAdd(CardPool *card_pool, CardData *card);

/**
 * @brief 刪除卡池中卡牌id為"card_id"的卡片
 * @param card_pool 卡池
 * @param card_id 要刪除的卡片id
 */
void CardPoolRemove(CardPool *card_pool, int card_id);

/**
 * @brief 在卡池中尋找id為"card_id"的卡片
 * @param card_pool 卡池
 * @param card_id 要尋找的卡片id
 * @return 找到則回傳true，否則回傳否
 */
bool CardPoolFind(CardPool *card_pool, int card_id);

#endif // _CARD_H_