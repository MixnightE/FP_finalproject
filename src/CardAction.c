#include <CardAction.h>

// void NormalAttack(Card *card, Player *player, Enemy *enemy, Field *field)
// {
//     player->energy -= card->energy;
//     int atk = card->value_atk;
//     enemy->def -= atk;
//     if (enemy->def < 0)
//     {
//         enemy->hp += enemy->def;
//         enemy->def = 0;
//     }
//     fprintf(stdout, "Player cause %d damage.\n", card->value_atk);
// }

// void Shield(Card *card, Player *player, Enemy *enemy, Field *field)
// {
//     player->energy -= card->energy;
//     player->def += card->value_def;
//     fprintf(stdout, "Player got %d shield.\n", card->value_def);
// }

void InfernalBlade(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    draw_card_random(CardPiled->drawCard);


    card_remove(CardPile->handCard, "InfernalBlade");
}

void Intimidate(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    //weak
    fprintf(stdout, "Player apply weak.\n");
    card_remove(CardPile->handCard, "Intimidate");
}

void Metallicize(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int def = card->value_def;
    if(card->isUpdated)
    {
        def += 1;
    }
    player->def += def;
    fprintf(stdout, "Player got %d shield.\n", def);
}

void PowerThrough(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int def = card->value_def;
    if(card->isUpdated)
    {
        def += 5;
    }
    //gain 2 wound
    player->def += def;
    fprintf(stdout, "Player got %d shield.\n", def);
}

void Pummel(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int n = 4;
    if(card->isUpdated)
    {
        n += 1;
    }
    for(int i = 0; i < n; i++)
    {
        int atk = card->value_atk;
        enemy->def -= atk;
        if (enemy->def < 0)
        {
            enemy->hp += enemy->def;
            enemy->def = 0;
        }
        fprintf(stdout, "Player cause %d damage.\n", card->value_atk);
    }
    card_remove(CardPile->handCard, "Pummel");
}

void Rage(Card *card, Player *player, Enemy *enemy, Field *field)
{

}

void Rampage(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
        enemy->def -= atk;
        if (enemy->def < 0)
        {
            enemy->hp += enemy->def;
            enemy->def = 0;
        }
        fprintf(stdout, "Player cause %d damage.\n", atk);
    if(card->isUpdated) card->value_atk += 8;
    else card->value_atk += 5;
}

void RecklessCharge(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    if(card->isUpdated)
    {
        atk += 3;
    }
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage.\n", atk);
    //shuffle dazed into draw pile
}

void SearingBlow(Card *card, Player *player, Enemy *enemy, Field *field)   
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    if(card->isUpdated)
    {
        atk += 4;
    }
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage.\n", atk);
    card->isUpdated = false;
}

void SecondWind(Card *card, Player *player, Enemy *enemy, Field *field)
{
    
}

void SeeingRed(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int energy = 1;
    if(card->isUpdated) energy += 1;
    player->energy += energy;
    fprintf(stdout, "Player got %d energy.\n", energy);
    card_remove(CardPile->handCard, "SeeingRed");
}

void Sentinel(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int def = card->value_def;
    if(card->isUpdated)
    {
        def += 3;
    }
    player->def += def;
    fprintf(stdout, "Player got %d shield.\n", def);
    if(card_find(CardPile->handCard, "Sentinel") == -1) 
    {
        int energy = 2;
        if(card->isUpdated)energy += 1;
        player->energy += energy;
    }   
}

void SeverSoul(Card *card, Player *player, Enemy *enemy, Field *field)
{

}

void ShockWave(Card *card, Player *player, Enemy *enemy, Field *field)
{
    //apply 3 weak and vulnerable to all enemies
    card_remove(CardPile->handCard, "ShockWave");
}

void Uppercut(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    enemy->def -= card->value_atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage.\n", card->value_atk);
    //apply 1 weak 1 vulnerable
}

void Whirlwind(Card *card, Player *player, Enemy *enemy, Field *field)
{
    for(int i = 0; i < player->energy; i++)
    {
        int atk = card->value_atk;
        if(card->isUpdated)
        {
            atk += 3;
        }
        enemy->def -= atk;
        if (enemy->def < 0)
        {
            enemy->hp += enemy->def;
            enemy->def = 0;
        }
        fprintf(stdout, "Player cause %d damage.\n", atk);
    }
    player->energy = 0;
}