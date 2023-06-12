#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <Card.h>

typedef struct EnemyData
{
    char *name;
    char *description;
    int hp;
    int max_hp;
    int def;
    BuffDeck buff;
    CardDeck deck;
} Enemy;

/**
 * @brief 初始化Enemy
 */
void enemy_initialize(Enemy *enemy);

#endif // _ENEMY_H_