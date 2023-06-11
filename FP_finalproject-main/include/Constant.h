#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <head.h>

#define DEBUG fprintf(stderr, "Now Running At %s file, %d line.\n", __FILE__, __LINE__);
#define EXIT DEBUG exit(0);

/* The Constant Macro of Player Data */

#define MAX_PLAYER_NAME_LENGTH 20

/* The Constant Macro of Card Data */

// 卡牌名稱最大字元數
#define MAX_NAME_LENGTH 20
// 卡牌概述最大字元數
#define MAX_DESCRIPTION_LENGTH 100

/* The Constant Macro of CardDeck Data */

// 角色最大可持有卡牌數量
#define MAX_DECK_SIZE 120
// 總共的牌數
#define MAX_CARD_NUM 150

#endif // _CONSTANT_H_