#include <EnemyAction.h>
#include <Field.h>
#include <Player.h>

void Cultist(Player* player,Enemy *enemy, Field *field)
{
    int value1 = 3;
    if(field->round == 0)
    {
        printf("Enemy next action: Gain %d atk", value1);
        break;
    }

    if(field->round % 2 == 1)
    {

    }
    else if (field->round % 2 == 0)
    {

    }
}