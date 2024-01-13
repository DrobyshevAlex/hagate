#include "../../defines.h"
#include "Cover.h"

const char *Cover::marshalJSON()
{
    DynamicJsonDocument jsonDoc(PAYLOAD_LEN);
    JsonObject entity = jsonDoc.to<JsonObject>();
    buildBaseField(&entity);

    entity[F("state")] = _state;
    entity[F("icon")] = "mdi:gate";
    entity[F("state_topic")] = _state_topic;
    entity[F("command_topic")] = _command_topic;
    entity[F("value_template")] = "{{ value_json.state }}";

    serializeJson(jsonDoc, _payload, PAYLOAD_LEN);

    return _payload;
}