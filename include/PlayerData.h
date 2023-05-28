#ifndef _PLAYER_DATA_H_
#define _PLAYER_DATA_H_

#include <Constant.h>
#include <CardData.h>

typedef struct playerDataType
{
    char name[MAX_PLAYER_NAME_LENGTH + 1]; // 名字
    int max_blood;                         // 最大血量
    int max_energy;                        // 最大能量值
    int max_card;                          // 最大手牌數
    CardData card;                         // 卡
} PlayerData;

#endif // _PLAYER_DATA_H_