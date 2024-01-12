#pragma once

#include <Arduino.h>
#include "../config/ConfigMgr.h"
#include "../mqtt/MQTT.h"
#include "entity/Device.h"

const char gateLabel[] = "Gate";
const char stateLabel[] = "State";

const char typeName[] = "gate";
const char gateName[] = "main";

#define TOPIC_SIZE 200

class DiscoveryMgr
{
public:
    DiscoveryMgr(MQTT *mqtt) : _mqtt(mqtt) {}
    void init();
    void loop();

private:
    void update();

private:
    MQTT *_mqtt;

private:
    bool _isSend = false;
    uint64_t _lastSendTime = 0;
};
