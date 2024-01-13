#pragma once

enum GateStatus
{
  GateStatusUnk = 0,
  GateStatusOpen,
  GateStatusOpening,
  GateStatusClosed,
  GateStatusClosing,
};

class GateState
{
public:
  GateStatus getStatus()
  {
    return _status;
  }

  void setStatus(GateStatus status)
  {
    _status = status;
  }

  bool operator==(GateState &o)
  {
    return _status == o._status;
  }

  bool operator!=(GateState &other)
  {
    return !(*this == other);
  }

private:
  GateStatus _status = GateStatusUnk;
};
