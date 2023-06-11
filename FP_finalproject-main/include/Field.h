#ifndef _FIELD_H_
#define _FIELD_H_

#include <Constant.h>
#include <head.h>
#include <Relic.h>
#include <Buff.h>

typedef struct FieldData
{
    RelicDeck relic;
    int round;
} Field;

/**
 * @brief 初始化field
 */
void field_initialize(Field *field);

#endif // _FIELD_H_