#ifndef _RELIC_H_
#define _RELIC_H_

#include <Constant.h>
#include <Player.h>
#include <Enemy.h>
#include <Field.h>

typedef struct RelicData
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    void (*function)(struct RelicData *Relic, Player *player, Enemy *enemy, Field *field);
} Relic;

#endif // _RELIC_H_