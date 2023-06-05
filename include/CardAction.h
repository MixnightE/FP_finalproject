#ifndef _ACTION_H_
#define _ACTION_H_

#include <Card.h>
#include <Player.h>
#include <Enemy.h>
#include <Field.h>

void NormalAttack(Card *card, Player *player, Enemy *enemy, Field *field);
void InfernalBlade(Card *card, Player *player, Enemy *enemy, Field *field);
void Intimidate(Card *card, Player *player, Enemy *enemy, Field *field);
void Metallicize(Card *card, Player *player, Enemy *enemy, Field *field);
void PowerThrough(Card *card, Player *player, Enemy *enemy, Field *field);
void Pummel(Card *card, Player *player, Enemy *enemy, Field *field);
void Rage(Card *card, Player *player, Enemy *enemy, Field *field);
void Rampage(Card *card, Player *player, Enemy *enemy, Field *field);
void RecklessCharge(Card *card, Player *player, Enemy *enemy, Field *field);
void SearingBlow(Card *card, Player *player, Enemy *enemy, Field *field);
void SeeingRed(Card *card, Player *player, Enemy *enemy, Field *field);
void Sentinel(Card *card, Player *player, Enemy *enemy, Field *field);
void SeverSoul(Card *card, Player *player, Enemy *enemy, Field *field);
void ShockWave(Card *card, Player *player, Enemy *enemy, Field *field);
void Uppercut(Card *card, Player *player, Enemy *enemy, Field *field);
void Whirlwind(Card *card, Player *player, Enemy *enemy, Field *field);
#endif // _ACTION_H_