#include <Player.h>

void player_initialize(Player *player, int hp, int energy)
{
    player->hp = hp;
    player->def = 0;
    player->energy = energy;
    card_pile_initialize(&(player->deck));
    buff_deck_initialize(&(player->buff));
}