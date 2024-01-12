#pragma once

#include <Arduino.h>
#include <ArduinoJSON.h>
#include <list>
#include "Base.h"

#define PAYLOAD_LEN 256

class Gate : Base
{
public:
    Gate(
        const char *name,
        Device *device,
        EntityCategory *entityCategory,
        const char *objectID,
        const char *uniqueID,
        bool forceUpdate) : Base(name, device, entityCategory, objectID, uniqueID, forceUpdate) {}
    const char *marshalJSON();

    void open(const char *currentTemperatureTemplate)
    {
        _state = 1;
    }

    void close(const char *currentTemperatureTopic)
    {
        _state = 2;
    }

private:
    uint8_t _state;

    char _payload[PAYLOAD_LEN] = {0};
};