#include <list>
#include "../defines.h"
#include "../utils/Utils.h"
#include "DiscoveryMgr.h"
#include "enum/EntityCategory.h"
#include "entity/Gate.h"

void DiscoveryMgr::init()
{
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
    if (
        !_mqtt->publish("test", "hello", true))
    {
        return;
    }

    _isSend = true;
}
