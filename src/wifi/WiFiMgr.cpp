#include <ESP8266WiFi.h>
#include "WiFiMgr.h"

void WiFiManager::connect()
{
  WiFiConfigData *data = _cnf->getWiFIConfigData();
  Serial.println("WiFi STA");
  WiFi.mode(WIFI_STA);
  WiFi.begin(data->ssid, data->password);
}

bool WiFiManager::isConnected()
{
  return WiFi.isConnected();
}
