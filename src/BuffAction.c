#include <BuffAction.h>
#include <FuncTable.h>

void Buff_Weak(Card *card, Player *player, Enemy *enemy, Field *field)
{
    card->atk = card->atk * 3 / 4;
}

void Buff_Vulnerable(Card *card, Player *player, Enemy *enemy, Field *field)
{
    int idx;
    if ((idx = find_buff_from_deck(&(player->buff), "Vulnerable")) == -1)
        return;
    card->atk *= 2;
}