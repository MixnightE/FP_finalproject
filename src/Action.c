#include <Action.h>

Card *buff_result(Card *card, Player *player, Enemy *enemy, Field *field, FuncTable *buffTable)
{
    Card *copied_card;
    for (int i = 0; i < 63; i++)
    {
        if (player->buff & (1 << i))
        {
            // act buff function
        }
    }
    return copied_card;
}

void card_action(Card *card, Player *player, Enemy *enemy, Field *field, FuncTable *cardTable)
{
    // act card function
}