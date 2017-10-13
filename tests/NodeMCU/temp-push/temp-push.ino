#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

ESP8266WiFiMulti WiFiMulti;
const char* ssid = "ssid";
const char* password = "pw";
int sleeper = 900000;

OneWire oneWire(D2);
DallasTemperature ds18b20(&oneWire);

void setup() {
  Serial.begin(9600);
  Serial.println(">>> Setup Start");
  WiFiMulti.addAP(ssid, password);
  Serial.println(">>> Setup WiFi");
  delay(10000);
}

void loop() {
  float currentTemp = getTemp();
  pushTemp(currentTemp);
  Serial.println("Temperatur: " + String(currentTemp));
  delay(sleeper);
}

void pushTemp(float temp) {
  HTTPClient http;
  http.begin("http://api.pushover.net/1/messages.json");
  http.POST("token=token&user=user&title=NodeMCU&message=Temperatur+" + String(temp));
  http.end();
}

float getTemp() {
  float temp;
  do {
    ds18b20.requestTemperatures();
    temp = ds18b20.getTempCByIndex(0);
  } while(temp==(85.0) || temp==(-127.0));
  return temp;
}
