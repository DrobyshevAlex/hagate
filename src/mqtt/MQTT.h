#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <list>
#include "MQTTConfig.h"
#include "../utils/Utils.h"
#include "Consumer.h"
#include "ESP8266WiFi.h"

class MQTT
{
public:
    MQTT(MQTTConfig *cnf) : _cnf(cnf)
    {
        _clientID = getChipID();
        _client.setClient(_wifiClient);
    }
    void init();
    void loop();
    void reconnect();
    bool publish(const char *topic, const char *payload, boolean retained)
    {
        if (_client.publish(topic, payload, retained))
        {
            Serial.printf("successful mqtt publish. topic: %s\n", topic);
            return true;
        }
        else
        {
            Serial.printf("failed mqtt publish. topic: %s\n", topic);
            return false;
        }
    }
    void subscribe(Consumer *consumer)
    {
        Serial.printf("MQTT subscribe: %s\n", consumer->getTopicName());

        _consumers.push_back(consumer);

        if (_client.connected())
        {
            _client.subscribe(consumer->getTopicName());
        }
    }

    bool isConnected()
    {
        return _client.connected();
    }

private:
    void callback(char *raw_topic, byte *raw_payload, unsigned int length);

    MQTTConfig *_cnf;
    WiFiClient _wifiClient;
    const char *_clientID;
    PubSubClient _client;
    uint64_t _lastReconnectTime = 0;
    bool _isConfigured;
    std::list<Consumer *> _consumers;
};
