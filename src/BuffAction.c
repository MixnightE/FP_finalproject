#include <BuffAction.h>

void Buff_Weak(Card *card, Player *player, Enemy *enemy, Field *field)
{
    card->atk = card->atk * 3 / 4;
}

void Buff_Vulnerable(Card *card, Player *player, Enemy *enemy, Field *field)
{
    card->atk = card->atk * 3 / 2;
}

void Buff_Ritual(Card *card, Player *player, Enemy *enemy, Field *field)
{
    int idx = find_buff_from_deck(&(enemy->buff), "Ritual");
    if (idx != -1)
        add_buff_into_deck(&(enemy->buff), "Strength", enemy->buff.deck[idx].level);
}

void Buff_Strength(Card *card, Player *player, Enemy *enemy, Field *field)
{
    int idx;
    if (player == NULL)
    {
        if ((idx = find_buff_from_deck(&(enemy->buff), "Strength")) != 1)
        {
            card->atk += enemy->buff.deck[idx].level;
        }
    }
    else if (enemy == NULL)
    {
        if ((idx = find_buff_from_deck(&(player->buff), "Strength")) != 1)
        {
            card->atk += player->buff.deck[idx].level;
        }
    }
}

void Buff_Block(Card *card, Player *player, Enemy *enemy, Field *field)
{
    int idx;
    if (player == NULL)
    {
        if ((idx = find_buff_from_deck(&(enemy->buff), "Block")) != 1)
        {
            enemy->def += enemy->buff.deck[idx].level;
        }
    }
    else if (enemy == NULL)
    {
        if ((idx = find_buff_from_deck(&(player->buff), "Block")) != 1)
        {
            player->def += player->buff.deck[idx].level;
        }
    }
}

void Buff_Rage(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Block", 3);
}