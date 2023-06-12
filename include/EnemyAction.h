#ifndef _ENEMY_ACTION_H_
#define _ENEMY_ACTION_H_

#include <Action.h>

// void function(Card *, Player *, Enemy *, Field *, CardTable *);

void Cultist(Player *player, Enemy *enemy, Field *field, CardTable *cardtable);

void Mouse(Player *player, Enemy *enemy, Field *field, CardTable *cardtable);

void Lagavulin(Player *player, Enemy *enemy, Field *field, CardTable *cardtable);

#endif // _ENEMY_ACTION_H_