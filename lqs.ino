// https://www.mischianti.org/2021/03/06/esp32-practical-power-saving-manage-wifi-and-cpu-1/
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html
// https://drive.google.com/file/d/1do7tb6tHbTQNlPX8fVwQQnwxOe8gZbed/view

#include <Adafruit_CCS811.h>
#include <HTTPClient.h>
#include <WiFi.h>

Adafruit_CCS811 ccs;
const char* ssid = "easybellMesh";
const char* password = "passwort";
String registerUrl = "http://192.168.178.28:8080/api/v1/controller.register";
String sendTvocUrl = "http://192.168.178.28:8080/api/v1/controller.sendDataTvoc";
String sendEco2Url = "http://192.168.178.28:8080/api/v1/controller.sendDataEco2";

String controllerName = "Kinderzimmer";

HTTPClient http;
int responseCode = -1;
String controllerId;


void setup() {
  Serial.begin(9600);
  Serial.println("begin");
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("waiting for wifi");
    delay(1000);
  }

  Serial.println("wifi connected");

  http.begin(registerUrl);
  http.addHeader("Content-Type", "application/json");
  responseCode = http.POST("{\"name\": \"" + String(controllerName) + "\"}");

  if (responseCode == 200) {
    controllerId = http.getString();
    Serial.println(controllerId);
  }

}

void loop() {

  http.begin(sendTvocUrl);
  http.addHeader("Content-Type", "application/json");
  int code = http.POST("{\"controllerId\": " + String(controllerId) + ", \"value\": 200}");
  http.begin(sendEco2Url);
  http.addHeader("Content-Type", "application/json");
  code = http.POST("{\"controllerId\": " + String(controllerId) + ", \"value\": 100}");
  delay(30000);
}
