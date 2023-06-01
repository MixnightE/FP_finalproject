#include <Card.h>
#include <cJSON.h>

Card *card_new(const char *name, int id, CardType type, int value, SpecialAbility specialAbility, const char *description)
{
    Card *newCard = (Card *)malloc(sizeof(Card));
    strcpy(newCard->name, name);
    newCard->id = id;
    newCard->type = type;
    if (type == TYPE_ATK)
        newCard->value.atk_value = value;
    else if (type == TYPE_DEF)
        newCard->value.def_value = value;
    else if (type == TYPE_AFF)
        newCard->value.aff_value = value;
    newCard->specialAbility = specialAbility;
    strcpy(newCard->description, description);
    return newCard;
}

// Card fireballCard = card_new("Fireball", 1, 1, 5, 0, 0, 0,"Deal 5 damage to the target.");
// Card healingPotionCard = card_new("Healing Potion", 2, 2, 0, 0, 10, 0,"Restore 10 health points to the player.");

CardDeck *card_deck_initialize(CardDeck *deck)
{
    deck->size = 0;
    return *deck;
}

void card_deck_add_by_name(CardDeck *cardDeck, const char *name)
{
}

// 根據卡牌名稱查找並返回卡牌
Card *card_deck_find_by_name(CardDeck *cardDeck, const char *name)
{
    for (int i = 0; i < cardDeck->size; i++)
    {
        if (strcmp(cardDeck[i].name, name) == 0)
        {
            return &cardDeck[i];
        }
    }
    return NULL;
}
