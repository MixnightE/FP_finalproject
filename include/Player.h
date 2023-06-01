#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <Buff.h>

typedef struct PlayerData
{
    int hp;
    int def; // 護盾
    Debuff debuff;
    Buff buff;
    int energy; // 行動次數
} Player;

#endif // _PLAYER_H_