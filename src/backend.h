#ifndef BACKEND_H_INCLUDED
#define BACKEND_H_INCLUDED

#include <Arduino.h>

class Backend
{
    public:
        void connectToWifi();
        void sendEco2(uint16_t value);
        void sendTvoc(uint16_t value);
        bool registerController();

};

#endif