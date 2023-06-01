#include <Card.h>
#include <cJSON.h>
#include <fileIO.h>

void card_create(const char *name, const char *description, char *func_name, void(*function), bool isUpdated, CardType type, FuncTable *ftable)
{
    cJSON *json = cJSON_Read("./data/card.json");
    cJSON *new_obj = cJSON_CreateObject();
    if (new_obj == NULL)
    {
        fprintf(stderr, "NermalAttack_create Error: Create object failed.\n");
        exit(1);
    }
    if (!cJSON_HasObjectItem(json, name))
    {
        ftable->data[ftable->size].name = func_name;
        ftable->data[ftable->size].fp = function;
        ftable->size++;
        cJSON_AddStringToObject(new_obj, "name", name);
        cJSON_AddStringToObject(new_obj, "description", description);
        cJSON_AddStringToObject(new_obj, "function", (const char *const)func_name);
        cJSON_AddBoolToObject(new_obj, "isUpdated", isUpdated);
        cJSON_AddNumberToObject(new_obj, "type", type);
        cJSON_AddItemToObject(json, name, new_obj);
        cJSON_Write("./data/card.json", json);
    }
    cJSON_Delete(json);
}

void card_deck_add(CardPile *cardPile, FuncTable *mappingTable, const char *name)
{
    cJSON *json = cJSON_Read("./data/card.json");
    cJSON *card_data = cJSON_GetObjectItemCaseSensitive(json, name);
    cardPile->deckCard.card[cardPile->deckCard.size].name = cJSON_GetObjectItemCaseSensitive(card_data, "name")->valuestring;
    cardPile->deckCard.card[cardPile->deckCard.size].description = cJSON_GetObjectItemCaseSensitive(card_data, "description")->valuestring;
    cardPile->deckCard.card[cardPile->deckCard.size].function = name_to_function_pointer(mappingTable, cJSON_GetObjectItemCaseSensitive(card_data, "function")->valuestring);
    cardPile->deckCard.card[cardPile->deckCard.size].isUpdated = cJSON_GetObjectItemCaseSensitive(card_data, "isUpdated")->type;
    cardPile->deckCard.card[cardPile->deckCard.size].type = cJSON_GetObjectItemCaseSensitive(card_data, "type")->valuedouble;
    cardPile->deckCard.size++;
}

int card_find(CardDeck *cardDeck, const char *name)
{
    for (int i = 0; i < cardDeck->size; i++)
    {
        if (!strcmp(name, cardDeck->card[i].name))
            return i;
    }
    return -1;
}

void card_deck_initialize(CardDeck *cardDeck)
{
    cardDeck->size = 0;
}

void card_pile_initialize(CardPile *cardPile)
{
    card_deck_initialize(&(cardPile->deckCard));
    card_deck_initialize(&(cardPile->drawCard));
    card_deck_initialize(&(cardPile->foldCard));
    card_deck_initialize(&(cardPile->handCard));
}

void card_assign(Card *card1, Card *card2)
{
    card1->description = card2->description;
    card1->function = card2->function;
    card1->isUpdated = card2->isUpdated;
    card1->name = card2->name;
    card1->type = card2->type;
}

int card_remove(CardDeck *cardDeck, const char *name)
{
    int idx;
    if ((idx = card_find(cardDeck, name)) == -1)
        return -1;
    for (int i = idx + 1; i < cardDeck->size; i++)
    {
        card_assign(cardDeck->card + i - 1, cardDeck->card + i);
    }
    cardDeck->size--;
    return 0;
}

void card_add(CardDeck *cardDeck, Card *card)
{
    card_assign(cardDeck->card + cardDeck->size, card);
    cardDeck->size++;
}

void fold_card(CardPile *cardPile, const char *name)
{
    int idx;
    if ((idx = card_remove(&(cardPile->handCard), name)) == -1)
    {
        fprintf(stderr, "Fold Card Error: The card %s didn't in your hand.\n", name);
        exit(1);
    }
}

void shuffle_card(CardPile *cardPile)
{
    for (int i = 0; i < cardPile->foldCard.size; i++)
    {
        card_assign(cardPile->drawCard.card + i, cardPile->foldCard.card + i);
    }
    cardPile->drawCard.size = cardPile->foldCard.size;
    cardPile->foldCard.size = 0;
}

void draw_card(CardPile *cardPile, const char *name)
{
    if (cardPile->drawCard.size == 0)
    {
        shuffle_card(cardPile);
    }
    for (int i = 0; i < cardPile->deckCard.size; i++)
    {
        if (!strcmp(name, cardPile->drawCard.card[i].name))
        {
            card_add(&(cardPile->handCard), cardPile->drawCard.card + i);
            card_remove(&(cardPile->drawCard), name);
            return;
        }
    }
}

void draw_card_random(CardPile *cardPile)
{
    if (cardPile->drawCard.size == 0)
    {
        shuffle_card(cardPile);
    }
    int idx = rand() % cardPile->drawCard.size;
    card_add(&(cardPile->handCard), cardPile->drawCard.card + idx);
    card_remove(&(cardPile->drawCard), cardPile->drawCard.card[idx].name);
}

void put_card(CardPile *cardPile)
{
    for (int i = 0; i < cardPile->deckCard.size; i++)
    {
        card_assign(cardPile->drawCard.card + i, cardPile->deckCard.card + i);
    }
    cardPile->drawCard.size = cardPile->deckCard.size;
}