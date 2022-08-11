#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include <Arduino.h>

class Sensor
{
    public:
        void begin();
        void iaqMeasure();
        void setBaseline(uint16_t eco2, uint16_t tvoc);
        void getAndWriteBaseline();
        uint16_t readEco2();
        uint16_t readTvoc();
};

#endif