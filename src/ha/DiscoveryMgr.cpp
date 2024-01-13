#include <list>
#include "../defines.h"
#include "../utils/Utils.h"
#include "DiscoveryMgr.h"
#include "enum/EntityCategory.h"
#include "entity/Cover.h"

void DiscoveryMgr::init()
{
}

void DiscoveryMgr::topicName(char *topic, const char *type, const char *uniqueID, const char *name)
{
    snprintf(topic, MAX_TOPIC_NAME, "%s/%s/%s/%s/config", _cnf->getDiscoveryConfigData()->prefix, type, uniqueID, name);
}

bool DiscoveryMgr::publishGateConfig(Device *device, const char *chipID)
{
    char uniqueID[32];
    snprintf(uniqueID, 32, "%s_hagate", chipID);
    DiscoveryConfigData *data = _cnf->getDiscoveryConfigData();

    topicName(
        _topic,
        "cover",
        chipID,
        "gate");
    Cover cnf(
        "Gate",
        device,
        entityCategoryConfig,
        "HomeGate",
        &uniqueID[0],
        true);
    cnf.setStateTopic(data->mqttStateTopic);
    cnf.setCommandTopic(data->mqttCommandTopic);

    Serial.println(cnf.marshalJSON());

    return _mqtt->publish(_topic, cnf.marshalJSON(), true);
}

void DiscoveryMgr::loop()
{
    if (!_isSend && (_lastSendTime + 1000) < millis())
    {
        update();
        _lastSendTime = millis();
    }
}

void DiscoveryMgr::update()
{
    Serial.println("DiscoveryMgr::update()");
    const char *macAddress = getMacAddress();
    const char *chipID = getChipID();

    const char *identifiers[1];
    identifiers[0] = macAddress;

    Device device;
    device.setHWVersion(hwVersion);
    device.setSWVersion(fwVersion);
    device.setModel(model);
    device.setName(name);
    device.setIdentifiers(identifiers, 1);
    device.setManufacturer(manufacturer);

    _isSend = publishGateConfig(&device, chipID);
    ;
}
