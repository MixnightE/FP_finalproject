
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