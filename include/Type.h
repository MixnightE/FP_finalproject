#ifndef _SPECIAL_ABILITY_H_
#define _SPECIAL_ABILITY_H_

typedef enum specialAbilityType
{
    none,
    sp01,
    sp02,
    sp03,
    // ...
} SpecialAbility;

typedef enum CardType
{
    TYPE_ATK, // 傷害
    TYPE_DEF, // 防禦
    TYPE_AFF  // 效果
} CardType;

#endif // _SPECIAL_ABILITY_H_