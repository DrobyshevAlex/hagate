#include <Arduino.h>
#include <ArduinoJson.h>
#include "utils/Utils.h"
#include "MQTT.h"

void MQTT::init()
{
    MQTTConfigData *data = _cnf->getMQTTConfigData();
    if (strlen(data->mqttHost) == 0)
    {
        return;
    }

    _client.setCallback([&](char *raw_topic, byte *raw_payload, unsigned int length)
                        { callback(raw_topic, raw_payload, length); });

    _wifiClient.setTimeout(MQTT_SOCKET_TIMEOUT * 1000);
    _client.setBufferSize(700);
    _client.setSocketTimeout(MQTT_SOCKET_TIMEOUT);
    _client.setServer(data->mqttHost, data->mqttPort);

    Serial.printf("MQTT client conn %s,  %d\r\n", data->mqttHost, data->mqttPort);

    _isConfigured = true;
}

void MQTT::reconnect()
{
    if (_client.connected())
    {
        return;
    }

    if (_lastReconnectTime + 1000 < millis())
    {
        MQTTConfigData *data = _cnf->getMQTTConfigData();
        Serial.printf("TRY conn %s, %s, %s\r\n", _clientID, data->mqttLogin, data->mqttPassword);
        if (_client.connect(_clientID, data->mqttLogin, data->mqttPassword))
        {
            Serial.println("CONN");
            for (auto consumer : _consumers)
            {
                _client.subscribe(consumer->getTopicName());
            }
            Serial.println("MQTT connected");
        }
        else
        {
            Serial.println("MQTT NOT connected");
            Serial.println(_client.state());
        }

        _lastReconnectTime = millis();
    }
}

void MQTT::callback(char *raw_topic, byte *raw_payload, unsigned int length)
{
    Serial.println("MQTT::callback");
    char *payload = (char *)malloc(length + 1);

    unsigned int i;
    for (i = 0; i < length; i++)
    {
        payload[i] = (char)raw_payload[i];
    }
    payload[i] = 0;

    Serial.printf("MQTT receive message. Topic: %s, Payload: %s\n", raw_topic, payload);

    for (auto consumer : _consumers)
    {
        if (strcmp(consumer->getTopicName(), raw_topic) == 0)
        {
            consumer->consume(payload);
        }
    }

    free((void *)payload);
}

void MQTT::loop()
{
    if (!_isConfigured)
    {
        return;
    }
    reconnect();
    _client.loop();
}
