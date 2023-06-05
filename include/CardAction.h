#ifndef _ACTION_H_
#define _ACTION_H_

#include <Card.h>
#include <Player.h>
#include <Enemy.h>
#include <Field.h>

void Strike(Card *card, Player *player, Enemy *enemy, Field *field);
void Defend(Card *card, Player *player, Enemy *enemy, Field *field);
void Bash(Card *card, Player *player, Enemy *enemy, Field *field);
void Anger(Card *card, Player *player, Enemy *enemy, Field *field);
void Armament(Card *card, Player *player, Enemy *enemy, Field *field);
void Body_Slam(Card *card, Player *player, Enemy *enemy, Field *field);
void Clash(Card *card, Player *player, Enemy *enemy, Field *field);
void Cleave(Card *card, Player *player, Enemy *enemy, Field *field);
void Clothesline(Card *card, Player *player, Enemy *enemy, Field *field);
void Headbutt(Card *card, Player *player, Enemy *enemy, Field *field);
void Heavy_Blade(Card *card, Player *player, Enemy *enemy, Field *field);
void Iron_Wave(Card *card, Player *player, Enemy *enemy, Field *field);
void Perfected_Strike(Card *card, Player *player, Enemy *enemy, Field *field);
void Pommel_Strike(Card *card, Player *player, Enemy *enemy, Field *field);
void Shrug_it_Off(Card *card, Player *player, Enemy *enemy, Field *field);
void Sword_Boomerang(Card *card, Player *player, Enemy *enemy, Field *field);
void Thunderclap(Card *card, Player *player, Enemy *enemy, Field *field);
void True_Grit(Card *card, Player *player, Enemy *enemy, Field *field);

#endif // _ACTION_H_
