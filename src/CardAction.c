#include <CardAction.h>

void NormalAttack(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage.\n", card->value_atk);
}

void Shield(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    player->def += card->value_def;
    fprintf(stdout, "Player got %d shield.\n", card->value_def);
}