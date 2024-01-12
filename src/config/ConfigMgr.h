#pragma once

#include <Arduino.h>
#include "../wifi/WiFiConfig.h"
#include "../mqtt/MQTTConfig.h"

class ConfigMgr : public WiFiConfig, public MQTTConfig
{
public:
    WiFiConfigData getWiFIConfigData();
    MQTTConfigData getMQTTConfigData();

private:
    uint16_t calculateChecksum(uint8_t *buf, uint16_t size);
};
