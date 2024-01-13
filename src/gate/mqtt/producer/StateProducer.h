#pragma once

#include <Arduino.h>
#include "../../../mqtt/MQTT.h"
#include "../../../ha/DiscoveryConfig.h"
#include "../../../mqtt/Producer.h"
#include "../entity/StateEntity.h"

class StateProducer : public Producer
{
public:
    StateProducer(MQTT *mqtt, DiscoveryConfigData *cnf) : Producer(mqtt)
    {
        strcpy(_topic, cnf->mqttStateTopic);
    }

    bool publish(StateEntity *state);
};
