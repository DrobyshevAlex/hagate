#pragma once

#include <Arduino.h>

class CommandEntity
{
public:
    bool unmarshalJSON(const char *data);

    char *getAction() { return _action; }

private:
    char _action[10];
};
