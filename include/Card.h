#ifndef _CARD_H_
#define _CARD_H_

#include <Buff.h>

#define TYPE_ATK (1)      // 攻擊卡
#define TYPE_SKL (1 << 1) // 技能卡
#define TYPE_ABL (1 << 2) // 能力卡

typedef struct CardData
{
    char *name;        // 卡片名稱
    char *description; // 卡片描述
    bool isExhaust;
    int type;
    int atk;
    int energy;
    BuffDeck buff;
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
 * @brief 將全部的手牌移到棄牌堆
 */
void drop_card(CardPile *deck);

/**
 * @brief 將deck中第idx張牌刪除
 */
void remove_card_by_idx(CardDeck *deck, int idx);

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

/**
 * @brief 將卡片名稱為name的卡片從json中找出並加入卡匣
 */
void add_card_into_deck(CardDeck *deck, const char *name);

/**
 * @brief 將deck中的卡牌印出來
 */
void print_card_deck(CardDeck *deck);

#endif // _CARD_H_