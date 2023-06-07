
#include <head.h>
#include <cJSON.h>
#include <fileIO.h>
#include <FuncTable.h>
#include <EnemyAction.h>
#include <BuffAction.h>
#include <CardAction.h>

void NormalAttack(Player *player, Enemy *enemy, Field *field)
{
    player->energy--;
    int atk = 6;
    atk -= enemy->def;
    if (atk <= 0)
        enemy->def -= 6;
    else
    {
        enemy->def = 0;
        enemy->hp -= atk;
    }
}

void Battle(Player *player, Enemy *enemy, Field *field, CardPile *cardPile)
{
    int choose_action;
    while (1)
    {
        do
        {
            scanf("%d", &choose_action);
            if (choose_action != -1)
                break;

            card_action(cardPile, choose_action, player, enemy, field);
        } while (player->energy > 0 && player->hp > 0 && enemy->hp > 0);

        if (player->hp <= 0)
        {
            printf("Game Over\n");
            break;
        }
        else if (enemy->hp <= 0)
        {
            printf("Win\n");
            break;
        }

        // Enemy_action(Player *player, Enemy *enemy, Field *field);

        if (player->hp <= 0)
        {
            printf("Game Over\n");
            break;
        }
        else if (enemy->hp <= 0)
        {
            printf("Win\n");
            break;
        }
    }
}

signed main(int argc, char *argv[])
{
    CardPile cardPile;
    FuncTable ftable;
    function_table_initialize(&ftable);
    card_pile_initialize(&cardPile);
    card_create("InfernalBlade", "Add a random card cost 0.\nExhaust.", InfernalBlade, false, TYPE_ATK, &ftable);
    card_create("Intimidate", "Apply 1 Weak to ALL enemies.\nExhaust.", Intimidate, false, TYPE_ATK, &ftable);
    card_create("Metallicize", "At the end of your turn, gain 3 Block.", Metallicize, false, TYPE_DEF, &ftable);
    card_create("PowerThrough", "Add 2 Wounds to your hand. Gain 15 Block.", PowerThrough, false, TYPE_DEF, &ftable);
    card_create("Pummel", "Deal 2 damage 4 times.\nExhaust.", Pummel, false, TYPE_ATK, &ftable);
    card_create("Rage", "Whenever you play Attack this turn, gain 3 Block.", Rage, false, TYPE_DEF, &ftable);
    card_create("Rampage", "Deal 8 damage. Increase this card's damage by 5.", Rampage, false, TYPE_ATK, &ftable);
    card_create("RecklessCharge", "Deal 7 damage. Shuffle a Dazed into your draw pile.", RecklessCharge, false, TYPE_ATK, &ftable);
    card_create("SearingBlow", "Deal 12 damage. Can be upgraded any number of times.", SearingBlow, false, TYPE_ATK, &ftable);
    card_create("SecondWind", "Exhaust all non-Attack cards in your hand and gain 5 Block for each card Exhausted.", SecondWind, false, TYPE_DEF, &ftable);
    card_create("SeeingRed", "Gain 2 energy.\nExhaust.", SeeingRed, false, TYPE_ATK, &ftable);
    card_create("Sentinel", "Gain 5 Block. If this card is Exhausted, gain 2 energy.", Sentinel, false, TYPE_DEF, &ftable);
    card_create("SeverSoul", "Exhaust all non-Attack cards in your hand. Deal 16 damage.", SeverSoul, false, TYPE_ATK, &ftable);
    card_create("ShockWave", "Apply 3 Weak and Icon Vulnerable Vulnerable to ALL enemies.\nExhaust.", ShockWave, false, TYPE_ATK, &ftable);
    card_create("Uppercut", "Deal 13 damage. Apply 1 Weak. Apply 1 Vulnerable.", Uppercut, false, TYPE_ATK, &ftable);
    card_create("Whirlwind", "Deal 5 damage to ALL enemies X times.", Whirlwind, false, TYPE_ATK, &ftable);
    card_create("Strike", "Deal 6(9) damage.", Strike, false, TYPE_ATK, &ftable);
    card_create("Defend", "Gain 5(8) shield.", Defend, false, TYPE_DEF, &ftable);
    card_create("Bash", "Deal 8(10) damage, apply 2(3) vulnerable.", Bash, false, TYPE_ATK, &ftable);
    card_create("Anger", "Deal 6(8) damage, add a copy of this card to the discard pile", Anger, false, TYPE_ATK, &ftable);
    card_create("Armament", "Gain 5 shield, upgrade a card in your hand.", Armament, false, TYPE_DEF, &ftable);
    card_create("Body Slam", "Deal damage equal to your current shield.", Body_Slam, false, TYPE_ATK, &ftable);
    card_create("Clash", "Deal 10(12) damage", Clash, false, TYPE_ATK, &ftable);
    card_create("Cleave", "Deal 8(11) damage to all enemy.", Cleave, false, TYPE_ATK, &ftable);
    card_create("Clothesline", "Deal 12(14) damage, apply 2 weak.", Clothesline, false, TYPE_ATK, &ftable);
    card_create("Headbutt", "Deal 9 damage, get a card from discard pile.", Headbutt, false, TYPE_ATK, &ftable);
    card_create("Heavy Blade", "Deal 14 damage.", Heavy_Blade, false, TYPE_ATK, &ftable);
    card_create("Iron Wave", "Deal 5 damage, and gain 5 shield.", Iron_Wave, false, TYPE_ATK, &ftable);
    card_create("Perfected Strike", "Deal 6 damage, and deal additional 2 damage if you have Strike.", Perfected_Strike, false, TYPE_ATK, &ftable);
    card_create("Pommel Strike", "Deal 9 damage, and draw 1 card.", Pommel_Strike, false, TYPE_ATK, &ftable);
    card_create("Shrug it Off", "Gain 8 shield, and draw 1 card.", Shrug_it_Off, false, TYPE_DEF, &ftable);
    card_create("Sword Boomerang", "Deal 3 damage to enemy 3 times.", Sword_Boomerang, false, TYPE_ATK, &ftable);
    card_create("Thunderclap", "Deal 4 damage, apply 1 vulnerable.", Thunderclap, false, TYPE_ATK, &ftable);
    card_create("True Grit", "Gain 7 shield, and random remove a card in hand.", True_Grit, false, TYPE_ATK, &ftable);
    return 0;
}
