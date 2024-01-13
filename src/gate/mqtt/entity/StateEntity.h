#pragma once

#include <Arduino.h>
#include "../../../defines.h"
#include "../../GateState.h"

class StateEntity
{
public:
    StateEntity(GateState *state) : _state(state) {}

    const char *marshalJSON();

private:
    GateState *_state;
    char _payload[50] = {0};
};
