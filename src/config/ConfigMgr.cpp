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

void ConfigMgr::load()
{
    strcpy(_wifi.ssid, WIFI_SSID);
    strcpy(_wifi.password, WIFI_PASSWORD);

    strcpy(_mqtt.mqttHost, MQTT_HOST);
    _mqtt.mqttPort = MQTT_PORT;
    strcpy(_mqtt.mqttLogin, MQTT_LOGIN);
    strcpy(_mqtt.mqttPassword, MQTT_PASSWORD);

    snprintf(_discovery.mqttStateTopic, MQTT_TOPIC_LEN, "hagate/%s/state", getChipID());
    snprintf(_discovery.mqttCommandTopic, MQTT_TOPIC_LEN, "hagate/%s/set", getChipID());
    strcpy(_discovery.prefix, MQTT_PREFIX);
}
