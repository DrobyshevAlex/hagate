#pragma once

#include "WiFiConfig.h"

class WiFiManager
{
public:
  WiFiManager(WiFiConfig *cnf) : _cnf(cnf) {}

  void connect();

  bool isConnected();

  WiFiConfig *_cnf;
};
