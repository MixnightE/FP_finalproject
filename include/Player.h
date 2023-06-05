#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <Constant.h>
#include <head.h>
#include <Buff.h>

typedef struct PlayerData
{
    int hp;
    int def; // 護盾
    BuffDeck buff;
    int energy; // 行動次數
} Player;

#endif // _PLAYER_H_