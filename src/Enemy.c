#include <Enemy.h>
#include <Player.h>
#include <Field.h>
#include <FuncTable.h>
#include <cJSON.h>
#include <Enemy.h>

void enemy_initialize(Enemy *enemy, const char *name, const char *description, const int atk, const int hp, const int def)
{
    enemy->name = name;
    enemy->description = description;
    enemy->atk = atk;
    enemy->hp = hp;
    enemy->def = def;
    card_deck_initialize(&(enemy->deck));
    buff_deck_initialize(&(enemy->buff));
}