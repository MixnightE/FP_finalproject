#ifndef _ACTION_H_
#define _ACTION_H_

#include <Card.h>
#include <Player.h>
#include <Enemy.h>
#include <Field.h>

void card_action(Card *card, Player *player, Enemy *enemy, Field *field);

void NormalAttack(Player *player, Enemy *enemy, Field *field);

#endif // _ACTION_H_