#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

ESP8266WiFiMulti WiFiMulti;
const char* ssid = "ssid";
const char* password = "pw";
int sleeper = 900000; // 15 min delay

OneWire oneWire(D2);
DallasTemperature ds18b20(&oneWire);

void setup() {
  Serial.begin(9600);
  Serial.println(">>> Setup Start");
  WiFiMulti.addAP(ssid, password);
  // 10 sec delay
  for(int i=10; i>0; i--) {
    Serial.println(">>> Countdown WiFi " + String(i));
    delay(1000); // 1 sec delay
  }
  Serial.println(">>> Setup WiFi");
  WiFi.mode(WIFI_STA);
  Serial.println(">>> Setup WiFi-Mode STA");
  Serial.println(">>> Setup All Ready");
}

void loop() {
  float currentTemp = getTemp();
  sendTemp(currentTemp);
  Serial.println(">>> Temperatur " + String(currentTemp));
  delay(sleeper);
}

void sendTemp(float temp) {
  HTTPClient http;
  http.begin("http://141.28.105.163/temp");
  http.addHeader("temp", String(temp));
  http.POST("");
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
