#pragma once

#include "mqtt/producer/StateProducer.h"
#include "GateState.h"

class Gate
{
public:
  Gate(
      StateProducer *stateProducer) : _stateProducer(stateProducer) {}
  void init();
  void loop();

  void open();
  void close();
  void stop();

private:
  void ext(uint8_t v);

private:
  StateProducer *_stateProducer;
  GateState _current;
  GateState _prev;

  uint8_t _ext = 0;

  bool _send = false;

  bool _btn1Was = false;
  unsigned long _lastBtn1Time = 0;
  bool _btn2Was = false;
  unsigned long _lastBtn2Time = 0;

  unsigned long _lastSendStateTime = 0;

  bool _openInProgress = false;
  unsigned long _lastOpenTime = 0;

  bool _closeInProgress = false;
  unsigned long _lastCloseTime = 0;

  bool _stopInProgress = false;
  unsigned long _lastStopTime = 0;
};
