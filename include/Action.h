#ifndef _ACTION_H_
#define _ACTION_H_

#include <BuffAction.h>

void enemy_new_round(Player *player, Enemy *enemy, Field *field);

void player_new_round(Player *player, Enemy *enemy, Field *field);

void enemy_choose_card(Player *player, Enemy *enemy, Field *field, CardTable *table, const char *name);

void player_choose_card(Player *player, Enemy *enemy, Field *field, CardTable *table, const char *name);

void enemy_buff_action(Card *card, Player *player, Enemy *enemy, Field *field);

void player_buff_action(Card *card, Player *player, Enemy *enemy, Field *field);

void print_battlefield(Player *player, Enemy *enemy, Field *field);

/**
 * @brief 創造卡片
 */
void card_create(char *name, const char *description, int type, int atk, bool isUpdated, int energy, void (*function)(Card *, Player *, Enemy *, Field *), CardTable *table);

/**
 * @brief 創造敵人
 */
void enemy_create(char *name, void (*function)(Card *, Player *, Enemy *, Field *, CardTable *), int hp, int def, CardDeck *deck, BuffDeck *buff, EnemyTable *table);

/**
 * @brief 創造buff
 */
void buff_create(char *name, const char *description, void (*function)(Card *, Player *, Enemy *, Field *));

/**
 * @brief 將卡片轉為名為name的卡片
 * @return 如果成功回傳卡片指針，失敗回傳NULL
 */
void card_deck_add(CardPile *cardPile, CardTable *mappingTable, const char *name);

void battle_over(Player *player, Enemy *enemy, Field *field);

#endif // _ACTION_H_