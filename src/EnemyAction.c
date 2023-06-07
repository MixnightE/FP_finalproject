#include <EnemyAction.h>

void Cultist(Card *card, Player *player, Enemy *enemy, Field *field, CardTable *cardtable)
{

    if (field->round % 2 == 1)
    {
        enemy_choose_card(player, enemy, field, cardtable, "Incantation");
    }
    else if (field->round % 2 == 0)
    {
        enemy_choose_card(player, enemy, field, cardtable, "DarkStrike");
    }
}