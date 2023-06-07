#ifndef _BUFF_ACTION_H_
#define _BUFF_ACTION_H_

#include <FuncTable.h>

void Buff_Weak(Card *card, Player *player, Enemy *enemy, Field *field);

void Buff_Ritual(Card *card, Player *player, Enemy *enemy, Field *field);

void Buff_Vulnerable(Card *card, Player *player, Enemy *enemy, Field *field);

void Buff_Strength(Card *card, Player *player, Enemy *enemy, Field *field);

void Buff_Defense(Card *card, Player *player, Enemy *enemy, Field *field);

void Buff_Inflame(Card *card, Player *player, Enemy *enemy, Field *field);

#endif // _BUFF_ACTION_H_