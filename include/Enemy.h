#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <Constant.h>
#include <Player.h>
#include <Enemy.h>
#include <Field.h>

typedef struct EnemyData
{
    char *name;
    char *description;
    int hp;
    int atk;
    int def;
    int buff_size;
    Buff buff[MAX_DECK_SIZE];
} Enemy;

void enemy_create(const char *name, const char *description, char *func_name, void (*function)(Player *, Enemy *, Field *), FuncTable *ftable);

int enemy_calculate_damage(Enemy *enemy, Field *field);

void print_enemy_damage(Enemy *enemy);

#endif // _ENEMY_H_