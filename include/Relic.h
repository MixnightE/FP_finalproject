#ifndef _RELIC_H_
#define _RELIC_H_

#include <Constant.h>
#include <Player.h>
#include <Enemy.h>
#include <Field.h>

typedef struct RelicData
{
    char *name;
    char *description;
    void(*function);
} Relic;

#endif // _RELIC_H_