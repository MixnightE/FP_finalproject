#include <CardAction.h>

void Strike(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    if(card->isUpdated)
    {
        atk+=3;
    }
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage.\n", atk);
}

void Defend(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int def = card->value_def;
    if(card->isUpdated)
    {
        def += 3;
    }
    player->def += def;
    fprintf(stdout, "Player got %d shield.\n", def);
}

void Bash(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    if(card->isUpdated)
    {
        atk += 2;
    }
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage, and apply 2 vulnerable\n", atk);
    //buff: apply 2(3) vulnerable
}

void Anger(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    if(card->isUpdated)
    {
        atk += 2;
    }
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    card_remove(cardDeck, "Anger");
    fprintf(stdout, "Player cause %d damage, and discard a copy of this card.\n", atk);
}

void Armament(Card *card, Player *player, Enemy *enemy, Field *field)
{
    //upgrade a card
    player->energy -= card->energy;
    player->def += card->value_def;

}

void Body_Slam(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = player->def;
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage.\n", player->def);
}

void Clash(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    if(card->isUpdated)
    {
        atk += 2;
    }
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage.\n", atk);
}

void Cleave(Card *card, Player *player, Enemy *enemy, Field *field)
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
}

void Clothesline(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    if(card->isUpdated)
    {
        atk += 2;
    }
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage, apply 2 weak.\n", card->value_atk);
    //buff: apply 2 weak
}

void Headbutt(Card *card, Player *player, Enemy *enemy, Field *field)
{

}

void Heavy_Blade(Card *card, Player *player, Enemy *enemy, Field *field)
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

void Iron_Wave(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    player->def += card->value_def;
    int atk = card->value_atk;
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage and got %d shield.\n", card->value_atk, card->value_def);
}

void Perfected_Strike(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    if(card_find(cardDeck, "Strike")) atk+=2;
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    fprintf(stdout, "Player cause %d damage.\n", card->value_atk);
    //差檢查strike
}

void Pommel_Strike(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    player->def += card->value_def;
    int atk = card->value_atk;
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    if(card->isUpdated)
    {
        draw_card_random(cardPile);
    }
    fprintf(stdout, "Player cause %d damage and draw cards.\n", card->value_atk);
}

void Shrug_it_Off(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    player->def += card->value_def;
    draw_card_random(cardPile);
    fprintf(stdout, "Player got %d shield and draw cards.\n", card->value_def);
}

void Sword_Boomerang(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    if(card->isUpdated){
        for(int i = 0; i < 4; i++)
        {
            enemy->def -= 3;
            if (enemy->def < 0)
            {
                enemy->hp += enemy->def;
                enemy->def = 0;
            }
        }
        fprintf(stdout, "Player got 12 shield and draw cards.\n");
    }

    else
    {
        for(int i = 0; i < 3; i++)
        {
            enemy->def -= 3;
            if (enemy->def < 0)
            {
                enemy->hp += enemy->def;
                enemy->def = 0;
            }
        }
    }
    fprintf(stdout, "Player cause 9 damage and draw cards.\n");
}

void Thunderclap(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int atk = card->value_atk;
    if(card_find(cardDeck, "Strike")) atk+=2;
    enemy->def -= atk;
    if (enemy->def < 0)
    {
        enemy->hp += enemy->def;
        enemy->def = 0;
    }
    //buff :vulnerable;
}

void True_Grit(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    player->def += card->value_def;
    fprintf(stdout, "Player got %d shield and exhaust a card.\n", card->value_def);
    //移除卡牌
}
