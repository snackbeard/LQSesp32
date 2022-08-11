#ifndef HIBERNATION_INCLUDED
#define HIBERNATION_INCLUDED

#include <Arduino.h>

class Hibernation
{
    public:
        void enableTouchWakeup();
        void startHibernation(uint32_t seconds);
        uint8_t getWakeupReason();

};

#endif