#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <Buff.h>

typedef struct PlayerData
{
    int hp;
    int def; // 護盾
    long long buff;
    int energy; // 行動次數
} Player;

int player_damage_calculate(Player *player, Field *field);

void print_player_data(Player *player);

#endif // _PLAYER_H_