#include<stdio.h>
#include<string.h>

typedef struct {
    char name[50];
    int type;   //卡片種類
    int value_1; // 數值123
    int value_2; //
    int value_3; //
    char description[100];

    int specialAbility; // 特殊能力（沒有就設為0)
} Card;

//創造卡
Card createCard(const char* name, int type, int value_1, int value_2, int value_3, int specialAbility,const char* description) {
    Card newCard;
    strcpy(newCard.name, name);
    newCard.type = type;
    newCard.value_1 = value_1;
    newCard.value_2 = value_2;
    newCard.value_3 = value_3;
    newCard.specialAbility = specialAbility;
    strcpy(newCard.description, description);
    return newCard;
}

// Card fireballCard = createCard("Fireball", 1, 5, 0, 0, 0,"Deal 5 damage to the target.");
// Card healingPotionCard = createCard("Healing Potion", 2, 0, 0, 10, 0,"Restore 10 health points to the player.");

#define MAX_CARDS 100

Card cardDeck[MAX_CARDS]; // 存储卡牌的數組
int numCards; // 卡牌數量

// 初始化卡牌數組
void initializeCardDeck() {
    numCards = 0;
    // 添加初始卡牌
    // cardDeck[numCards++] = ...;
    // cardDeck[numCards++] = ...;
    // ...
}

// 添加新卡牌到卡牌數組
void addCardToDeck(Card newCard) {
    if (numCards < MAX_CARDS) {
        cardDeck[numCards++] = newCard;
    }
}

// 根據卡牌名稱查找並返回卡牌
Card* findCardByName(const char* name) {
    for (int i = 0; i < numCards; i++) {
        if (strcmp(cardDeck[i].name, name) == 0) {
            return &cardDeck[i];
        }
    }
    return NULL;
}
