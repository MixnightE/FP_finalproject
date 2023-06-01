#ifndef _CARD_H_
#define _CARD_H_

#include <Constant.h>
#include <head.h>
#include <Type.h>

typedef union EffectValueUnion
{
    int atk_value; // attack value
    int def_value; // defend value
    int aff_value; // affect value
} Effect;

typedef struct CardData
{
    int id;                                        // 卡片編號
    char name[MAX_CARD_NAME_LENGTH];               // 卡片名稱
    CardType type;                                 // 卡片種類
    Effect value;                                  // 卡片屬性
    char description[MAX_CARD_DESCRIPTION_LENGTH]; // 卡片描述
    SpecialAbility ability;                        // 特殊能力（沒有就設為0)
} Card;

typedef struct CardDeckData
{
    int size;
    int deck[MAX_CARDPOOL_SIZE]; // 記錄卡片id
} CardDeck;

/**
 * @brief 創建一張新的卡片
 * @return 新的卡片
 * @param name 卡片名稱
 * @param id 卡片編號
 * @param type 卡片型態(TYPE_ATK攻擊, TYPE_DEF防禦, TYPE_AFF效果選一)
 * @param value 卡片數值(傷害值、防禦值、效果值等)
 * @param specialAbility 特殊效果編號
 * @param description 卡片描述
 */
Card *card_new(const char *name, int id, CardType type, int value, SpecialAbility specialAbility, const char *description);

/**
 * @brief 將卡牌新增進card.json中
 */

/**
 * @brief 卡匣初始化
 */
CardDeck *card_deck_initialize(CardDeck *deck);

/**
 * @brief 新增卡片進卡池
 * @param card_pool 卡池
 * @param card 要新增的卡片
 */
void card_deck_add_by_name(CardDeck *cardDeck, const char *name);

/**
 * @brief 刪除卡池中卡牌id為"card_id"的卡片
 * @param card_pool 卡池
 * @param card_id 要刪除的卡片id
 */
void card_deck_remove(CardDeck *cardDeck, int card_id);

/**
 * @brief 在卡池中尋找id為"card_id"的卡片
 * @param card_pool 卡池
 * @param card_id 要尋找的卡片id
 * @return 找到則回傳卡片，否則回傳NULL
 */
Card *card_deck_find_by_id(CardDeck *cardDeck, int card_id);

/**
 * @brief 在卡池中尋找name為“name"的卡片
 * @return 找到則回傳卡片，否則回傳NULL
 */
Card *card_deck_find_by_name(CardDeck *cardDeck, const char *name);

#endif // _CARD_H_