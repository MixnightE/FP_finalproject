#include <EnemyAction.h>

void Cultist(Player *player, Enemy *enemy, Field *field, CardTable *cardtable)
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

void Mouse(Player *player, Enemy *enemy, Field *field, CardTable *cardtable)
{
    if (field->round % 3 == 1)
    {
        enemy_choose_card(player, enemy, field, cardtable, "Chomp");
    }
    else if (field->round % 3 == 2)
    {
        enemy_choose_card(player, enemy, field, cardtable, "Thrash");
    }
    else if (field->round % 3 == 0)
    {
        enemy_choose_card(player, enemy, field, cardtable, "Bellow");
    }
}

void Lagavulin(Player *player, Enemy *enemy, Field *field, CardTable *cardtable)
{
    if (field->round <= 3 && enemy->def > 0)
    {
        return ;
    }
    
    if (field->round % 2 == 1)
    {
        enemy_choose_card(player, enemy, field, cardtable, "LagavulinAttack");
    }
    else if (field->round % 2 == 0)
    {
        enemy_choose_card(player, enemy, field, cardtable, "SiphonSoul");
    }
}