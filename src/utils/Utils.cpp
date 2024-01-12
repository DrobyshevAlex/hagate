#include "Utils.h"
#include "ESP8266WiFi.h"

char _macStr[19] = {0};
char _macAddress[18] = {0};

const char *getMacAddress()
{
    if (strlen(_macAddress) > 0)
    {
        return _macAddress;
    }

    const char *chipId = WiFi.macAddress().c_str();
    snprintf(
        _macAddress,
        18,
        "%02X:%02X:%02X:%02X:%02X:%02X",
        chipId[0],
        chipId[1],
        chipId[2],
        chipId[3],
        chipId[4],
        chipId[5]);
    return _macAddress;
}

const char *getChipID()
{
    if (strlen(_macStr) > 0)
    {
        return _macStr;
    }

    uint32_t mac = ESP.getChipId();
    snprintf(_macStr, 19, "0x%x", mac);

    return _macStr;
}
