#ifndef _FIELD_H_
#define _FIELD_H_

#include <Constant.h>
#include <Relic.h>

typedef struct FieldData
{
    Relic relic[MAX_DECK_SIZE];
    int round;
} Field;

#endif // _FIELD_H_