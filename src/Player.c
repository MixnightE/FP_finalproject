#include <Player.h>

void player_initialize(Player *player, int hp)
{
    player->hp = hp;
    player->def = 0;
    card_pile_initialize(&(player->deck));
    buff_deck_initialize(&(player->buff));
}