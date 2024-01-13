#include "Gate.h"

void Gate::init()
{
  ext(0);
}

void Gate::ext(uint8_t v)
{
  _ext = v;
  digitalWrite(OUT_LATCH, LOW);
  shiftOut(OUT_DP, OUT_CLK, MSBFIRST, _ext);
  digitalWrite(OUT_LATCH, HIGH);
}

void Gate::loop()
{
  ulong ms = millis();
  if (!_openInProgress && !_closeInProgress)
  {
    bool btn1 = _btn1Was;
    if (_lastBtn1Time + 500 < ms && digitalRead(BTN1) != _btn1Was)
    {
      btn1 = !btn1;
      _lastBtn1Time = ms;

      if (!btn1)
      {
        _current.setStatus(GateStatusOpen);
      }
      else if (_current.getStatus() == GateStatusOpen)
      {
        _current.setStatus(GateStatusClosing);
        _closeInProgress = true;
        _lastCloseTime = ms;
      }

      _btn1Was = btn1;
    }

    bool btn2 = _btn2Was;
    if (_lastBtn2Time + 50 < ms && digitalRead(BTN2) != _btn2Was)
    {
      btn2 = !btn2;
      _lastBtn2Time = ms;

      if (!btn2)
      {
        _current.setStatus(GateStatusOpen);
      }
      else if (_current.getStatus() == GateStatusClosed)
      {
        _current.setStatus(GateStatusOpening);
        _openInProgress = true;
        _lastOpenTime = ms;
      }

      _btn2Was = btn2;
    }
  }

  if ((_lastSendStateTime + 100) < ms)
  {
    if (_current != _prev || !_send)
    {
      StateEntity state(&_current);
      _send = _stateProducer->publish(&state);
      _prev = _current;
    }

    _lastSendStateTime = ms;
  }

  if (_openInProgress && (_lastOpenTime + 2000) < ms)
  {
    ext(bitClear(_ext, EXT_OPEN));
    _openInProgress = false;
    Serial.println("OPEN end");
  }
  if (_closeInProgress && (_lastCloseTime + 2000) < ms)
  {
    ext(bitClear(_ext, EXT_CLOSE));
    _closeInProgress = false;
    Serial.println("CLOSE end");
  }
  if (_stopInProgress && (_lastStopTime + 2000) < ms)
  {
    ext(bitClear(_ext, EXT_STOP));
    _stopInProgress = false;
    Serial.println("STOP end");
  }
}

void Gate::open()
{
  if (_openInProgress)
  {
    return;
  }

  Serial.println("OPEN");

  _openInProgress = true;
  _current.setStatus(GateStatusOpening);
  ext(1 << EXT_OPEN);
  _lastOpenTime = millis();
  Serial.printf("state %d\n", _current.getStatus());
}

void Gate::close()
{
  if (_closeInProgress)
  {
    return;
  }

  Serial.println("CLOSE");

  _closeInProgress = true;
  _current.setStatus(GateStatusClosing);

  ext(1 << EXT_CLOSE);
  _lastCloseTime = millis();
  Serial.printf("state %d\n", _current.getStatus());
}

void Gate::stop()
{
  if (_stopInProgress)
  {
    return;
  }

  Serial.println("STOP");

  _stopInProgress = true;
  if (_current.getStatus() == GateStatusClosing)
  {
    _current.setStatus(GateStatusClosed);
  }
  else if (_current.getStatus() == GateStatusOpening)
  {
    _current.setStatus(GateStatusOpen);
  }
  ext(1 << EXT_STOP);
  _lastStopTime = millis();
  Serial.printf("state %d\n", _current.getStatus());
}
