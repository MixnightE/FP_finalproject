#ifndef _BUFF_H_
#define _BUFF_H_

#include <Constant.h>

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

#endif // _BUFF_H_