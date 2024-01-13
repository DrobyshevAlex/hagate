#pragma once

#include <Arduino.h>
#include "../wifi/WiFiConfig.h"
#include "../mqtt/MQTTConfig.h"
#include "../ha/DiscoveryConfig.h"

class ConfigMgr : public WiFiConfig, public MQTTConfig, public DiscoveryConfig
{
public:
    void load();

    WiFiConfigData *getWiFIConfigData()
    {
        return &_wifi;
    }
    MQTTConfigData *getMQTTConfigData()
    {
        return &_mqtt;
    }
    DiscoveryConfigData *getDiscoveryConfigData()
    {
        return &_discovery;
    }

private:
    uint16_t calculateChecksum(uint8_t *buf, uint16_t size);

    WiFiConfigData _wifi;
    MQTTConfigData _mqtt;
    DiscoveryConfigData _discovery;
};
