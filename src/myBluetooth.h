#ifndef MYBLUETOOTH_H_INCLUDED
#define MYBLUETOOTH_H_INCLUDED

#include <Arduino.h>

class MyBluetooth
{
    public:
        void begin();
        void end();
        String read();
        void write(char message);

};

#endif