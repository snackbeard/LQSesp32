#include "sensor.h"
#include "Adafruit_SGP30.h"
#include "backend.h"
#include "myPreferences.h"

Adafruit_SGP30 sgp;
MyPreferences myP;

void Sensor::begin()
{
    if (!sgp.begin())
    {
        Serial.println("Sensor not found");
        while (1);
    }
}

void Sensor::iaqMeasure()
{
    if (!sgp.IAQmeasure()) {
        Serial.println("Measurement failed");
        return;
    }
}

void Sensor::getAndWriteBaseline()
{
    myP.begin();
    uint16_t TVOC_base, eCO2_base;
    if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
      Serial.println("Failed to get baseline readings");
      return;
    }

    myP.writeBaseEco2(eCO2_base);
    myP.writeBaseTvoc(TVOC_base);
    myP.end();
}

void Sensor::setBaseline(uint16_t eco2, uint16_t tvoc)
{
    sgp.setIAQBaseline(eco2, tvoc);
}

uint16_t Sensor::readEco2()
{
    return sgp.eCO2;
}

uint16_t Sensor::readTvoc()
{
    return sgp.TVOC;
}