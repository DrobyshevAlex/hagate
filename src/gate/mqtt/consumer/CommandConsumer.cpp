#include <Arduino.h>
#include "CommandConsumer.h"
#include "../entity/CommandEntity.h"

void CommandConsumer::consume(const char *payload)
{
    Serial.printf("CommandConsumer::consume: %s\n", payload);

    CommandEntity command;
    if (!command.unmarshalJSON(payload))
    {
        Serial.printf("cant unmarshal command");
        return;
    }

    Serial.print("Command: ");
    Serial.println(command.getAction());
    if (strcmp("OPEN", command.getAction()) == 0)
    {
        _gate->open();
    }
    else if (strcmp("CLOSE", command.getAction()) == 0)
    {
        _gate->close();
    }
    else if (strcmp("STOP", command.getAction()) == 0)
    {
        _gate->stop();
    }
}
