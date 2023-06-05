
#include <head.h>
#include <Buff.h>
#include <Card.h>
#include <cJSON.h>
#include <Constant.h>
#include <Enemy.h>
#include <Field.h>
#include <fileIO.h>
#include <FuncTable.h>
#include <Player.h>
#include <Relic.h>

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
