#include <Arduino.h>
#include "defines.h"
#include "config/ConfigMgr.h"
#include "wifi/WiFiMgr.h"
#include "mqtt/MQTT.h"
#include "ha/DiscoveryMgr.h"
#include "ESP8266HTTPClient.h"

ConfigMgr cnf;
WiFiManager wifiManager(&cnf);
MQTT *mqtt;
DiscoveryMgr *discoveryMgr;

void setup()
{
  Serial.begin(SERIAL_SPEED);

  pinMode(LED, OUTPUT);

  wifiManager.connect();

  mqtt = new MQTT(&cnf);
  mqtt->init();

  discoveryMgr = new DiscoveryMgr(mqtt);
  discoveryMgr->init();
}

WiFiClient wifiClient;
void loop()
{
  uint16 ms;
  if (wifiManager.isConnected())
  {
    discoveryMgr->loop();
    mqtt->loop();
    ms = 1000;
  }
  else
  {
    ms = 100;
  }
  digitalWrite(LED, HIGH);
  delay(ms);
  digitalWrite(LED, LOW);
  delay(ms);
}
