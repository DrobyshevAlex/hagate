#pragma once

#include <Arduino.h>

#define HOST_LEN 33
#define MQTT_LOGIN_LEN 33
#define MQTT_PASSWORD_LEN 33
#define MQTT_TOPIC_LEN 65

struct MQTTConfigData
{
  char mqttHost[HOST_LEN] = {0};
  uint16_t mqttPort = 0;
  char mqttLogin[MQTT_LOGIN_LEN] = {0};
  char mqttPassword[MQTT_PASSWORD_LEN] = {0};
  bool mqttIsHADiscovery = true;
};

class MQTTConfig
{
public:
  virtual MQTTConfigData *getMQTTConfigData() = 0;
};
