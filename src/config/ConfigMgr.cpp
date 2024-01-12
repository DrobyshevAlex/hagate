#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include "../defines.h"
#include "../utils/Utils.h"
#include "ConfigMgr.h"
#include "default.h"

uint16_t ConfigMgr::calculateChecksum(uint8_t *buf, uint16_t size)
{
    uint16_t crc = 0xffff, poly = 0xa001;
    uint16_t i = 0;
    uint16_t len = size - 2;

    for (i = 0; i < len; i++)
    {
        crc ^= buf[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x01)
            {
                crc >>= 1;
                crc ^= poly;
            }
            else
                crc >>= 1;
        }
    }

    return crc;
}

WiFiConfigData ConfigMgr::getWiFIConfigData()
{
    WiFiConfigData data;
    strcpy(data.ssid, WIFI_SSID);
    strcpy(data.password, WIFI_PASSWORD);
    return data;
}

MQTTConfigData ConfigMgr::getMQTTConfigData()
{
    MQTTConfigData data;
    strcpy(data.mqttHost, MQTT_HOST);
    data.mqttPort = MQTT_PORT;
    strcpy(data.mqttLogin, MQTT_LOGIN);
    strcpy(data.mqttPassword, MQTT_PASSWORD);
    strcpy(data.mqttHADiscoveryPrefix, MQTT_PREFIX);

    snprintf(data.mqttStateTopic, MQTT_TOPIC_LEN, "hagate/%s/state", getChipID());
    snprintf(data.mqttCommandTopic, MQTT_TOPIC_LEN, "hagate/%s/set", getChipID());
    return data;
}
