
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

        if(player->hp <= 0)
        {
            printf("Game Over\n");
            break;
        }
        else if(enemy->hp <= 0)
        {
            printf("Win\n");
            break;
        }

        // Enemy_action(Player *player, Enemy *enemy, Field *field);

        if(player->hp <= 0)
        {
            printf("Game Over\n");
            break;
        }
        else if(enemy->hp <= 0)
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
    card_create("NormalAttack", "Deal 6 damage.", "NormalAttack", NormalAttack, false, TYPE_ATK, &ftable);
    card_deck_add(&cardPile, &ftable, "NormalAttack");
    card_deck_add(&cardPile, &ftable, "NormalAttack");
    card_deck_add(&cardPile, &ftable, "NormalAttack");
    card_deck_add(&cardPile, &ftable, "NormalAttack");
    card_deck_add(&cardPile, &ftable, "NormalAttack");
    card_deck_add(&cardPile, &ftable, "NormalAttack");
    card_deck_add(&cardPile, &ftable, "NormalAttack");
    put_card(&cardPile);
    draw_card(&cardPile, "NormalAttack");
    draw_card_random(&cardPile);
    fold_card(&cardPile, "NormalAttack");
    fold_card(&cardPile, "12345");


    return 0;
}