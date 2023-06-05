#ifndef _ACTION_H_
#define _ACTION_H_

#include <Player.h>
#include <Enemy.h>
#include <Field.h>
#include <Card.h>

Card *buff_result(Card *card, Player *player, Enemy *enemy, Field *field, FuncTable *buffTable);

void card_action(Card *card, Player *player, Enemy *enemy, Field *field, FuncTable *cardTable);

#endif // _ACTION_H_