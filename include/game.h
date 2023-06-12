#ifndef _GAME_H_
#define _GAME_H_

#include <gtk/gtk.h>
#include <Battle.h>

typedef struct GameData
{
    GtkWidget *window;
    GtkWidget *stack;
    Card *card;
    Player *player;
    Enemy *enemy;
    Field *field;
    CardTable *cardtable;
    BuffTable *bufftable;
    EnemyTable *enemytable;
} Game;

void game_initialize(Game *game, Card *card, Player *player, Enemy *enemy, Field *field, CardTable *cardtable, BuffTable *bufftable, EnemyTable *enemytable);

void all_initialize(Player *player, Enemy *enemy, Field *field, CardTable *cardtable, EnemyTable *enemytable, BuffTable *bufftable);

void basic_card_add(Player *player);

char *random_enemy_name(EnemyTable *enemytable);

#endif // _GAME_H_