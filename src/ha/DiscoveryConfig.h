#pragma once

#include <Arduino.h>

#define HA_PREFIX_LEN 17
#define MQTT_TOPIC_LEN 65

struct DiscoveryConfigData
{
  char prefix[HA_PREFIX_LEN] = {0};
  char mqttCommandTopic[MQTT_TOPIC_LEN] = {0};
  char mqttStateTopic[MQTT_TOPIC_LEN] = {0};
};

class DiscoveryConfig
{
public:
  virtual DiscoveryConfigData *getDiscoveryConfigData() = 0;
};
