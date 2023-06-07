#include <Enemy.h>

void enemy_initialize(Enemy *enemy)
{
    card_deck_initialize(&(enemy->deck));
    buff_deck_initialize(&(enemy->buff));
}