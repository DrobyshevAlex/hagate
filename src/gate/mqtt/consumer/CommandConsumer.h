#pragma once

#include <Arduino.h>
#include "mqtt/Consumer.h"
#include "../../Gate.h"

class CommandConsumer : public Consumer
{
public:
    CommandConsumer(Gate *gate) : _gate(gate) {}
    void consume(const char *payload);

private:
    Gate *_gate;
};
