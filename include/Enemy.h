#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <Constant.h>
#include <head.h>
#include <Buff.h>

typedef struct EnemyData
{
    char *name;
    char *description;
    int hp;
    int atk;
    int def;
    BuffDeck buff;
} Enemy;

#endif // _ENEMY_H_