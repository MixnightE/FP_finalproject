#ifndef _BATTLE_H_
#define _BATTLE_H_

#include <CardAction.h>
#include <EnemyAction.h>
// #include <RelicAction.h>

void call_enemy(Enemy *enemy, char *name);

void Battle(Player *player, Enemy *enemy, Field *field, CardTable *cardtable, EnemyTable *enemytable, BuffTable *bufftable);

#endif // _BATTLE_H_
