#include <Card.h>

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
    buff_deck_initialize(&(card1->buff));
    card1->name = card2->name;
    card1->description = card2->description;
    card1->isUpdated = card2->isUpdated;
    card1->type = card2->type;
    card1->energy = card2->energy;
    card1->atk = card2->atk;
    for (int i = 0; i < card2->buff.size; i++)
        card1->buff.deck[(card1->buff.size)++] = card2->buff.deck[i];
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

void add_card_into_deck(CardDeck *deck, const char *name)
{
    Card *card = &(deck->card[deck->size]);
    cJSON *json = cJSON_Read("./data/card.json");
    cJSON *card_data = cJSON_GetObjectItem(json, name);
    card->atk = cJSON_GetObjectItem(card_data, "atk")->valueint;
    // cJSON *buff_data = cJSON_GetObjectItem(card_data, "buff");
    // if (buff_data != NULL && cJSON_IsObject(buff_data))
    // {
    //     cJSON *item = buff_data->child;
    //     card->buff.size = 0;
    //     while (item != NULL)
    //     {
    //         if (cJSON_IsNumber(item))
    //         {
    //             card->buff.deck[card->buff.size].name = item->string;
    //             card->buff.deck[card->buff.size].level = item->valueint;
    //             card->buff.size++;
    //         }
    //         item = item->next;
    //     }
    // }
    card->description = cJSON_GetObjectItem(card_data, "description")->valuestring;
    card->energy = cJSON_GetObjectItem(card_data, "energy")->valueint;
    card->name = cJSON_GetObjectItem(card_data, "name")->valuestring;
    card->type = cJSON_GetObjectItem(card_data, "type")->valueint;
    deck->size++;
}

void print_card_deck(CardDeck *deck)
{
    for (int i = 0; i < deck->size; i++)
    {
        fprintf(stdout, "%s: %s\n", deck->card[i].name, deck->card[i].description);
    }
}