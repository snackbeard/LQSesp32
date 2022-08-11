#include "myPreferences.h"
#include <Preferences.h>

Preferences prefs;

void MyPreferences::begin()
{
    prefs.begin("lqs", false);
}

void MyPreferences::end()
{
    prefs.end();
}

uint16_t MyPreferences::readBaseTvoc()
{
    return prefs.getUShort("tvocbase", 0);
}

void MyPreferences::writeBaseTvoc(uint16_t tvocbase)
{
    prefs.putUShort("tvocbase", tvocbase);
}

uint16_t MyPreferences::readBaseEco2()
{
    return prefs.getUShort("eco2base", 0);
}

void MyPreferences::writeBaseEco2(uint16_t eco2base)
{
    prefs.putUShort("eco2base", eco2base);
}

bool MyPreferences::readInitialSetup()
{
    return prefs.getBool("initSetup", true);
}

void MyPreferences::writeInitialSetup(bool state)
{
    prefs.putBool("initSetup", state);
}

bool MyPreferences::readFinishedSetup()
{
    return prefs.getBool("fSetup", false);
}

void MyPreferences::writeFinishedSetup(bool state)
{
    prefs.putBool("fSetup", state);
}

String MyPreferences::readControllerName()
{
    return prefs.getString("cName", "");
}

void MyPreferences::writeControllerName(String cName)
{
    prefs.putString("cName", cName);
}

uint32_t MyPreferences::readControllerId()
{
    return prefs.getShort("cId", 0);
}

void MyPreferences::writeControllerId(uint32_t cId)
{
    prefs.putShort("cId", cId);
}

String MyPreferences::readPort()
{
    return prefs.getString("port", "");
}

void MyPreferences::writePort(String port)
{
    prefs.putString("port", port);
}

String MyPreferences::readServerIp()
{
    return prefs.getString("serverIp", "");
}

void MyPreferences::writeServerIp(String serverIp)
{
    prefs.putString("serverIp", serverIp);
}

String MyPreferences::readSsid()
{
    return prefs.getString("ssid", "");
}

void MyPreferences::writeSsid(String ssid)
{
    prefs.putString("ssid", ssid);
}

String MyPreferences::readPassword()
{
    return prefs.getString("password", "");
}

void MyPreferences::writePassword(String password)
{
    prefs.putString("password", password);
}

void MyPreferences::clear()
{
    prefs.clear();
    prefs.end();
    Serial.println("Preferences cleared");
}

bool MyPreferences::writeNewConfig(String message)
{
    Serial.print("writing new config: "); Serial.println(message);
    uint8_t pos = 0;
    uint8_t configCounter = 0;
    String token;

    while (pos != -1)
    {
        pos = message.indexOf('?');
        token = message.substring(0, pos);
        message.remove(0, pos + 1); // + 1 weil '?' der delimiter ist

        /*
        switch (configCounter)
        {
            case 0: writeSsid(token); break;
            case 1: writePassword(token); break;
            case 2: writeServerIp(token); break;
            case 3: writePort(token); break;
            case 4: writeControllerName(token); break;
            default: break;
        }
        */

        configCounter++;       
    }

    if (configCounter == 5) return true;
    return false;
}