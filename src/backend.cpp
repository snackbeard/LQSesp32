#include "backend.h"
#include <HTTPClient.h>
#include "myPreferences.h"

MyPreferences pref;
HTTPClient http;

void Backend::connectToWifi()
{
    pref.begin();
    WiFi.begin(pref.readSsid().c_str(), pref.readPassword().c_str());
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.println("waiting for wifi ...");
        delay(1000);
    }
    pref.end();
    Serial.println("connected to wifi!");
}

bool Backend::registerController()
{

    pref.begin();
    bool success = false;
    Serial.println(pref.readServerIp());
    Serial.println(pref.readPort());
    Serial.println(pref.readControllerName());

    http.begin("http://" + pref.readServerIp() + ":" + pref.readPort() + "/api/v1/controller.register");
    http.addHeader("Content-Type", "application/json");
    uint8_t responseCode = http.POST("{\"name\": \"" + pref.readControllerName() + "\"}");

    if (responseCode == 200) {
        pref.writeControllerId(http.getString().toInt());
        success = true;
    }
    pref.end();
    return success;
}

void Backend::sendEco2(uint16_t value)
{
    pref.begin();
    http.begin("http://" + pref.readServerIp() + ":" + pref.readPort() + "/api/v1/controller.sendDataTvoc");
    http.addHeader("Content-Type", "application/json");
    http.POST("{\"controllerId\": " + String(pref.readControllerId()) + ", \"value\": " + value + "}");
    pref.end();
}

void Backend::sendTvoc(uint16_t value)
{
    pref.begin();
    http.begin("http://" + pref.readServerIp() + ":" + pref.readPort() + "/api/v1/controller.sendDataEco2");
    http.addHeader("Content-Type", "application/json");
    http.POST("{\"controllerId\": " + String(pref.readControllerId()) + ", \"value\": " + value + "}");
    pref.end();
}