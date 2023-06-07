#include <Field.h>

void field_initialize(Field *field)
{
    field->round = 0;
    relic_deck_initialize(&(field->relic));
}