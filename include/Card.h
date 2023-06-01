#ifndef _CARD_H_
#define _CARD_H_

#include <Constant.h>
#include <head.h>
#include <Player.h>
#include <Enemy.h>
#include <Field.h>

typedef enum CardType
{
    TYPE_ATK, // 傷害
    TYPE_AFF, // 效果
    TYPE_STG, // 狀態
    TYPE_CRV  // 詛咒
} CardType;

typedef struct CardData
{
    char name[MAX_NAME_LENGTH];               // 卡片屬性
    char description[MAX_DESCRIPTION_LENGTH]; // 卡片描述
    bool isUpdated;
    CardType type;
    void (*function)(struct CardData *card, Player *player, Enemy *enemy, Field *field);
} Card;

typedef struct CardDeckData
{
    int size;
    int card[MAX_DECK_SIZE]; // 記錄卡片id
} CardDeck;

#endif // _CARD_H_