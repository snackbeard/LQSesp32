#ifndef MYPREFERENCES_H_INCLUDED
#define MYPREFERENCES_H_INCLUDED

#include <Arduino.h>

class MyPreferences
{
    public:

        void clear();
        void begin();
        void end();
        bool writeNewConfig(String config);

        String readSsid();
        String readPassword();
        String readServerIp();
        String readPort();
        String readControllerName();
        uint32_t readControllerId();
        bool readFinishedSetup();
        bool readInitialSetup();
        uint16_t readBaseEco2();
        uint16_t readBaseTvoc();
        void writeSsid(String ssid);
        void writePassword(String password);
        void writeServerIp(String serverIp);
        void writePort(String port);
        void writeControllerName(String name);
        void writeControllerId(uint32_t cId);
        void writeFinishedSetup(bool state);
        void writeInitialSetup(bool state);
        void writeBaseEco2(uint16_t eco2Base);
        void writeBaseTvoc(uint16_t tvocBase);
};

#endif