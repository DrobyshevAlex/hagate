#pragma once

#include <Arduino.h>
#include "../config/ConfigMgr.h"
#include "../mqtt/MQTT.h"
#include "entity/Device.h"
#include "DiscoveryConfig.h"

const char gateLabel[] = "Gate";
const char stateLabel[] = "State";

const char typeName[] = "gate";
const char gateName[] = "main";

#define TOPIC_SIZE 256
#define MAX_TOPIC_NAME 128

class DiscoveryMgr
{
public:
    DiscoveryMgr(DiscoveryConfig *cnf, MQTT *mqtt) : _cnf(cnf), _mqtt(mqtt) {}
    void init();
    void loop();

    void topicName(char *topic, const char *type, const char *uniqueID, const char *name);
    bool publishGateConfig(Device *device, const char *chipID);

private:
    void update();

private:
    DiscoveryConfig *_cnf;
    MQTT *_mqtt;

private:
    bool _isSend = false;
    uint64_t _lastSendTime = 0;
    char _topic[MAX_TOPIC_NAME] = {0};
};
