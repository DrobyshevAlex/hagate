#include <ArduinoJson.h>

#include "defines.h"
#include "CommandEntity.h"

bool CommandEntity::unmarshalJSON(const char *data)
{
    strcpy(_action, data);
    return true;
}