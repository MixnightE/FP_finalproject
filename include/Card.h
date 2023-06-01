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

/**
 * @brief 初始化卡池
 */
void card_pile_initialize(CardPile *cardPile);

/**
 * @brief 初始化卡匣(如果pile已經初始化，就不用初始化這個了)
 */
void card_deck_initialize(CardDeck *cardDeck);

/**
 * @brief 將卡片2的內容複製給卡片1
 */
void card_assign(Card *card1, Card *card2);

/**
 * @brief 將卡匣內名為name的卡刪除
 */
int card_remove(CardDeck *cardDeck, const char *name);

/**
 * @brief 將卡新增進卡匣
 */
void card_add(CardDeck *cardDeck, Card *card);

/**
 * @brief 將名為name的卡從手牌移到棄牌堆
 */
void fold_card(CardPile *cardPile, const char *name);

/**
 * @brief 將所有的棄牌全部洗回抽牌堆
 */
void shuffle_card(CardPile *cardPile);

/**
 * @brief 將抽牌堆中名為name的牌移到手牌堆
 */
void draw_card(CardPile *cardPile, const char *name);

/**
 * @brief 將抽排堆的隨機一張牌移到手牌堆
 */
void draw_card_random(CardPile *cardPile);

/**
 * @brief 將卡匣內的卡複製進抽牌堆中(戰鬥開始時用)
 */
void put_card(CardPile *cardPile);

#endif // _CARD_H_