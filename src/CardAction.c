#include <CardAction.h>

// --通用函式--------------------------------------------------------
void player_deal_damage(Card *card, Player *player, Enemy *enemy)
{
    if (enemy->def < card->atk)
    {
        enemy->hp -= card->atk - enemy->def;
        enemy->def = 0;
    }
    else
    {
        enemy->def -= card->atk;
    }
}

void enemy_deal_damage(Card *card, Player *player, Enemy *enemy)
{
    int idx;
    if ((idx = find_buff_from_deck(&(player->buff), "Block")) == -1)
    {
        player->hp -= card->atk;
    }
    else if (player->buff.deck[idx].level <= card->atk)
    {
        player->hp -= card->atk - player->buff.deck[idx].level;
        remove_buff_from_deck(&(player->buff), "Block");
    }
    else
    {
        player->buff.deck[idx].level -= card->atk;
    }
}
// --通用函式--------------------------------------------------------

// --敵人的卡--------------------------------------------------------
// Cultist
void Incantation(Card *card, Player *player, Enemy *enemy, Field *field)
{
    FILE *fp = fopen("./data/message.txt", "a");
    fprintf(fp, "Cultist gain 3 Ritual.\n");
    fclose(fp);
    add_buff_into_deck(&(enemy->buff), "Ritual", 3);
}
void DarkStrike(Card *card, Player *player, Enemy *enemy, Field *field)
{
    enemy_deal_damage(card, player, enemy);
}
// Mouse
void Chomp(Card *card, Player *player, Enemy *enemy, Field *field)
{
    enemy_deal_damage(card, player, enemy);
}
void Thrash(Card *card, Player *player, Enemy *enemy, Field *field)
{
    enemy_deal_damage(card, player, enemy);
    add_buff_into_deck(&(enemy->buff), "Block", 5);
}
void Bellow(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(enemy->buff), "Strength", 3);
    add_buff_into_deck(&(enemy->buff), "Block", 6);
}
// --敵人的卡--------------------------------------------------------

/*
範例
給玩家加六點護盾（Block）
add_buff_into_deck(&(player->buff), "Block", 6);
給敵人二點Vulnerable
add_buff_into_deck(&(enemy->buff), "Vulnerable", 2);
對敵人造成傷害
player_deal_damage(card, player, enemy); // atk已經在卡裡面了 除非是有破盾效果的傷害要另外寫
對玩家造成傷害
enemy_deal_damage(card, player, enemy);
*/
// --玩家的卡--------------------------------------------------------
void Strike(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
}

void Defend(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Block", 6);
}

void Bash(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
    add_buff_into_deck(&(enemy->buff), "Vulnerable", 2);
}

void Inflame(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Strength", 2);
}

void InfernalBlade(Card *card, Player *player, Enemy *enemy, Field *field)
{
    draw_card_random(&(player->deck));
}

void Intimidate(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(enemy->buff), "Weak", 2);
}

void Anger(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
    fold_card(&(player->deck), "Anger");
}

void Cleave(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
}

void Clothesline(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
    add_buff_into_deck(&(enemy->buff), "Weak", 2);
}

void Flex(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Strength", 2);
}

void Heavy_Blade(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
}

void Iron_Wave(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Block", 5);
    player_deal_damage(card, player, enemy);
}

void Perfected_Strike(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
    if (card_find(&(player->deck.handCard), "Strike") != -1)
    {
        if (enemy->def < 2)
        {
            enemy->hp -= 2 - enemy->def;
            enemy->def = 0;
        }
        else
        {
            enemy->def -= 2;
        }
    }
}

void Pommel_Strike(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
    draw_card_random(&(player->deck));
}

void Shrug_it_Off(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Block", 8);
    draw_card_random(&(player->deck));
}

void Sword_Boomerang(Card *card, Player *player, Enemy *enemy, Field *field)
{
    for (int i = 0; i < 3; i++)
    {
        player_deal_damage(card, player, enemy);
    }
}

void Thunderclap(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
    add_buff_into_deck(&(enemy->buff), "Vulnerable", 1);
}

void True_Grit(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Block", 7);
    // exhaust
}
void Metallicize(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Block", 3);
}

/*
void PowerThrough(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy -= card->energy;
    int def = card->value_def;
    if(card->isExhaust)
    {
        def += 5;
    }
    //gain 2 wound
    player->def += def;
    fprintf(stdout, "Player got %d shield.\n", def);
}
*/

void Pummel(Card *card, Player *player, Enemy *enemy, Field *field)
{
    int n = 4;
    for (int i = 0; i < n; i++)
    {
        player_deal_damage(card, player, enemy);
    }
}

void Rage(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Rage", 1);
}

void Rampage(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
    card->atk += 5;
}

// void Rupture(Card *card, Player *player, Enemy *enemy, Field *field)
// {
//     if(enemy_deal_damage) add_buff_into_deck(&(player->buff), "Strength", 1);
// }

void SearingBlow(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
}
/*
void SecondWind(Card *card, Player *player, Enemy *enemy, Field *field)
{
    //Exhaust all non-Attack cards
}
*/
void SeeingRed(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->energy += 2;
}

void Sentinel(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Block", 5);
}

void SeverSoul(Card *card, Player *player, Enemy *enemy, Field *field)
{
    // Exhaust all non-Attack
}

void ShockWave(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(enemy->buff), "Weak", 3);
    add_buff_into_deck(&(enemy->buff), "Vulnerable", 3);
}

void Uppercut(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
    add_buff_into_deck(&(enemy->buff), "Weak", 1);
    add_buff_into_deck(&(enemy->buff), "Vulnerable", 1);
}

void Whirlwind(Card *card, Player *player, Enemy *enemy, Field *field)
{
    for (int i = 0; i < player->energy; i++)
    {
        player_deal_damage(card, player, enemy);
    }
    player->energy = 0;
}
void TwinStrike(Card *card, Player *player, Enemy *enemy, Field *field)
{
    for (int i = 0; i < 2; i++)
    {
        player_deal_damage(card, player, enemy);
    }
}

void Warcry(Card *card, Player *player, Enemy *enemy, Field *field)
{
    // 沒實作出"Put a card from your hand  onto the top of your draw pile"
    draw_card_random(&(player->deck));
}

void WildStrike(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
}

void BattleTrance(Card *card, Player *player, Enemy *enemy, Field *field)
{
    for (int i = 0; i < 3; i++)
    {
        draw_card_random(&(player->deck));
    }
}

void BloodforBlood(Card *card, Player *player, Enemy *enemy, Field *field)
{
    // 沒實作出"Costs 1 less RedEnergy for each time you lose HP this combat"
    player_deal_damage(card, player, enemy);
}

void Bloodletting(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->hp -= 3;
    player->energy += 2;
}

void BurningPact(Card *card, Player *player, Enemy *enemy, Field *field)
{
    for (int i = 0; i < 2; i++)
    {
        draw_card_random(&(player->deck));
    }
}

void Carnage(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player_deal_damage(card, player, enemy);
}

void Combust(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->hp -= 1;
    player_deal_damage(card, player, enemy);
}

void Disarm(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(enemy->buff), "Strength", -2);
}

void Entrench(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Block", player->def);
}

void Evolve(Card *card, Player *player, Enemy *enemy, Field *field)
{
    draw_card_random(&(player->deck));
}

void FeelNoPain(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Block", 3);
}

void GhostlyArmor(Card *card, Player *player, Enemy *enemy, Field *field)
{
    add_buff_into_deck(&(player->buff), "Block", 10);
}

void Hemokinesis(Card *card, Player *player, Enemy *enemy, Field *field)
{
    player->hp -= 2;
    player_deal_damage(card, player, enemy);
}
