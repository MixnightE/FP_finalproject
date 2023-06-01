#ifndef _CARD_H_
#define _CARD_H_

#include <Constant.h>
#include <head.h>
#include <FuncTable.h>

typedef enum CardType
{
    TYPE_ATK, // 傷害
    TYPE_AFF, // 效果
    TYPE_STG, // 狀態
    TYPE_CRV  // 詛咒
} CardType;

typedef struct CardData
{
    char *name;        // 卡片屬性
    char *description; // 卡片描述
    bool isUpdated;
    CardType type;
    void(*function);
} Card;

typedef struct CardDeckData
{
    int size;
    Card card[MAX_DECK_SIZE]; // 記錄卡片id
} CardDeck;

typedef struct CardPileData
{
    CardDeck handCard;
    CardDeck foldCard;
    CardDeck drawCard;
    CardDeck deckCard;
} CardPile;

/**
 * @brief 創造卡片
 */
void card_create(const char *name, const char *description, char *func_name, void(*function), bool isUpdated, CardType type, FuncTable *ftable);

/**
 * @brief 將卡片轉為名為name的卡片
 * @return 如果成功回傳卡片指針，失敗回傳NULL
 */
void card_deck_add(CardPile *cardPile, FuncTable *mappingTable, const char *name);

/**
 * @brief 找到cardDeck中的name卡片
 * @return 如果成功回傳idx，否則回傳-1
 */
int card_find(CardDeck *cardDeck, const char *name);

void card_pile_initialize(CardPile *cardPile);
void card_deck_initialize(CardDeck *cardDeck);
void card_assign(Card *card1, Card *card2);
int card_remove(CardDeck *cardDeck, const char *name);
void card_add(CardDeck *cardDeck, Card *card);
void fold_card(CardPile *cardPile, const char *name);
void shuffle_card(CardPile *cardPile);
void draw_card(CardPile *cardPile, const char *name);
void draw_card_random(CardPile *cardPile);
void put_card(CardPile *cardPile);

#endif // _CARD_H_