#include <Arduino.h>
#include "backend.h"
#include "sensor.h"
#include "myPreferences.h"
#include "myBluetooth.h"
#include "hibernation.h"
#include <BluetoothSerial.h>

#define SETUP_TIME 86400 // == 24 hours for burn in time
#define INTERVAL 900 // == 15 minutes, for sending data in setup

MyBluetooth b;
Hibernation h;
MyPreferences p;
Backend backend;
Sensor sensor;

BluetoothSerial btSerial;

int counterSetup = 0;
uint8_t sMeasureCount = 0;

bool startConfiguration = false;


void setup() {

  setCpuFrequencyMhz(80);

  Serial.begin(9600);
  
  Serial.println("hallo");
  h.enableTouchWakeup();
  
  h.enableTouchWakeup();
  uint8_t reason = h.getWakeupReason();

  // wait for touch wakeup if never configured
  if (p.readInitialSetup() && reason != 1)
  {
    Serial.println("initalSetup, going to deepsleep forever, waiting for touch wakeup");
    h.startHibernation(0);
  }

  // touch wakeup, enables bluetooth for configuration
  if (reason == 1)
  {
    Serial.println("wakeup reason is 1, starting bluetooth");
    b.begin();
    Serial.println("waiting for client connection");
    startConfiguration = true;
  }

  // will be skipped if esp32 woke up by touch -> needs to be configured first
  if (!startConfiguration)
  {
    sensor.begin();

    if (p.readBaseEco2() != 0 && p.readBaseTvoc() != 0)
    {
      sensor.setBaseline(p.readBaseEco2(), p.readBaseTvoc());
      Serial.println("baseline set");
    }

    backend.connectToWifi();

    if (p.readControllerId() == 0)
    {
      // controller has no ID, request one from server
      bool success = backend.registerController();
      if (!success)
      {
        Serial.println("failed to get controller ID");
        // do something with led
      }
    }

  }

}

void loop() {

  Serial.println("loop");



  if (startConfiguration)
  {
    // bluetooth read & answer write here
    // config store here
  }
  else
  {
    sensor.iaqMeasure();

    if (!p.readFinishedSetup())
    {
      if (counterSetup < SETUP_TIME)
      {
        Serial.println("still running setup");
        if (counterSetup % INTERVAL)
        {
          backend.sendEco2(sensor.readEco2());
          backend.sendTvoc(sensor.readTvoc());
        }

        counterSetup++;

        if (counterSetup == SETUP_TIME - 1)
        {
          sensor.getAndWriteBaseline();
          p.writeFinishedSetup(true);
        }

      }
    }
    else
    {
      if (sMeasureCount == 20)
      {
        backend.sendEco2(sensor.readEco2());
        backend.sendTvoc(sensor.readTvoc());
        h.startHibernation(INTERVAL);
      }
      sMeasureCount++;
    }
  
  }

  delay(1000);

}