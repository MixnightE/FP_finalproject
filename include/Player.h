#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <Card.h>

typedef struct PlayerData
{
    int hp;
    int def; // 護盾
    BuffDeck buff;
    CardPile deck;
    int energy; // 行動次數
} Player;

/**
 * @brief 初始化Player
 */
void player_initialize(Player *player);

#endif // _PLAYER_H_