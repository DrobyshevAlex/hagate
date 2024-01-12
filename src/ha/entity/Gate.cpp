#include "../../defines.h"
#include "Gate.h"

const char *Gate::marshalJSON()
{
    DynamicJsonDocument jsonDoc(PAYLOAD_LEN);
    JsonObject entity = jsonDoc.to<JsonObject>();
    buildBaseField(&entity);

    entity[F("state")] = _state;

    serializeJson(jsonDoc, _payload, PAYLOAD_LEN);

    return _payload;
}