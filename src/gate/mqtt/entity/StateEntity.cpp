#include <ArduinoJson.h>
#include "StateEntity.h"
#include "defines.h"

const char *StateEntity::marshalJSON()
{
    DynamicJsonDocument jsonDoc(50);
    JsonObject entity = jsonDoc.to<JsonObject>();

    switch (_state->getStatus())
    {
    case GateStatusOpen:
        entity[F("state")] = "open";
        break;
    case GateStatusOpening:
        entity[F("state")] = "opening";
        break;
    case GateStatusClosed:
        entity[F("state")] = "closed";
        break;
    case GateStatusClosing:
        entity[F("state")] = "closing";
        break;

    default:
        break;
    }

    serializeJson(jsonDoc, _payload, 50);

    return _payload;
}
