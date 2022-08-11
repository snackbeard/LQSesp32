#include "myBluetooth.h"
#include "myPreferences.h"
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

String MyBluetooth::read()
{
    String config = SerialBT.readStringUntil(' ');
    Serial.print("recieved data: "); Serial.println(config);
    return config;
}

void MyBluetooth::write(char message)
{
    SerialBT.write(message);
}

void MyBluetooth::begin()
{
    SerialBT.begin("ESP32");
}

void MyBluetooth::end()
{
    SerialBT.end();
}