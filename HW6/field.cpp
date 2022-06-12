#include "field.h"

Field::Field(String pattern) : pattern(pattern){}

Field::~Field() {}

bool Field::match(String packet)
{
    return match_value(packet);
}
