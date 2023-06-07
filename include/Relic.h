#ifndef _RELIC_H_
#define _RELIC_H_

#include <Buff.h>

typedef struct RelicData
{
    char *name;
    char *description;
    BuffDeck buff;
} Relic;

typedef struct RelicDeckData
{
    int size;
    Relic deck[MAX_DECK_SIZE];
} RelicDeck;

/**
 * @brief 初始化RelicDeck
 */
void relic_deck_initialize(RelicDeck *deck);

#endif // _RELIC_H_