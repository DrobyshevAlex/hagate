#include <Arduino.h>
#include "defines.h"
#include "config/ConfigMgr.h"
#include "wifi/WiFiMgr.h"
#include "mqtt/MQTT.h"
#include "ha/DiscoveryMgr.h"
#include "ESP8266HTTPClient.h"
#include "gate/mqtt/producer/StateProducer.h"
#include "gate/mqtt/consumer/CommandConsumer.h"
#include "gate/Gate.h"

ConfigMgr cnf;
WiFiManager wifiManager(&cnf);
MQTT *mqtt;
DiscoveryMgr *discoveryMgr;
StateProducer *stateProducer;
CommandConsumer *commandConsumer;
Gate *gate;

void setup()
{
  Serial.begin(SERIAL_SPEED);

  pinMode(LED, OUTPUT);
  pinMode(OUT_DP, OUTPUT);
  pinMode(OUT_LATCH, OUTPUT);
  pinMode(OUT_CLK, OUTPUT);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);

  cnf.load();

  wifiManager.connect();

  mqtt = new MQTT(&cnf);
  mqtt->init();

  discoveryMgr = new DiscoveryMgr(&cnf, mqtt);
  discoveryMgr->init();

  stateProducer = new StateProducer(mqtt, cnf.getDiscoveryConfigData());

  gate = new Gate(stateProducer);
  gate->init();

  commandConsumer = new CommandConsumer(gate);
  commandConsumer->init(cnf.getDiscoveryConfigData()->mqttCommandTopic);
  mqtt->subscribe(commandConsumer);
}

ulong _last = 0;
void loop()
{
  uint16 ms;
  if (wifiManager.isConnected())
  {
    discoveryMgr->loop();
    gate->loop();
    mqtt->loop();
    ms = 1000;
  }
  else
  {
    ms = 100;
  }

  ulong cur = millis();
  if (_last + ms < cur)
  {
    _last = cur;
    if (digitalRead(LED))
    {
      digitalWrite(LED, LOW);
    }
    else
    {
      digitalWrite(LED, HIGH);
    }
  }
}
