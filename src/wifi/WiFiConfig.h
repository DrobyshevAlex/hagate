#pragma once

#define WIFI_SSID_LEN 33
#define WIFI_PWD_LEN 65

struct WiFiConfigData
{
  char ssid[WIFI_SSID_LEN] = {0};
  char password[WIFI_PWD_LEN] = {0};
};

class WiFiConfig
{
public:
  virtual WiFiConfigData *getWiFIConfigData() = 0;
};
