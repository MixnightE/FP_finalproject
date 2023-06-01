#ifndef _BUFF_H_
#define _BUFF_H_

#include <Constant.h>
typedef struct BuffData
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    void(*function);
} Buff;

typedef struct DebuffData
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    void(*function);
} Debuff;

#endif // _BUFF_H_