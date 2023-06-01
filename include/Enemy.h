#ifndef _ENEMY_H_
#define _ENEMY_H_

typedef struct EnemyData
{
    char *name;
    char *description;
    void (*function)(Player *, Enemy *, Field *);
    int hp;
    int atk;
    int def;
    Buff buff;
    Debuff debuff;
} Enemy;

void enemy_create(const char *name, const char *description, char *func_name, void (*function)(Player *, Enemy *, Field *), FuncTable *ftable);

#endif // _ENEMY_H_