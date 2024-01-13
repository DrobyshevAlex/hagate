#include "StateProducer.h"

bool StateProducer::publish(StateEntity *state)
{
    const char *payload = state->marshalJSON();
    Serial.printf("payload: %s\n", payload);
    return _mqtt->publish(_topic, payload, true);
}
