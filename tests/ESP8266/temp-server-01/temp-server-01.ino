#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "ssid";
const char* password = "pw";
ESP8266WebServer server(80);

OneWire oneWire(2);
DallasTemperature ds18b20(&oneWire);

void setup() {
  Serial.begin(9600);
  setConnection();
  setServer();
  Serial.println(">>> Ready");
}

void loop() {
  server.handleClient();
}

void getTemp() {
  float currentTemp = readTemp();
  server.send(200, "text/plain", "Temperatur: " + String(currentTemp));
  Serial.println(">>> Temp ausgelesen: " + String(currentTemp));
}

void getTest() {
  server.send(200, "text/plain", "ESP01: Test");
  Serial.println(">>> Test");
}

float readTemp() {
  float temp;
  do {
    ds18b20.requestTemperatures();
    temp = ds18b20.getTempCByIndex(0);
  } while(temp==(85.0) || temp==(-127.0));
  return temp;
}

void setConnection() {
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print(">>> SSID: ");
  Serial.println(ssid);
  Serial.print(">>> IP: ");
  Serial.println(WiFi.localIP());
}

void setServer() {
  server.on("/temp", getTemp);
  server.on("/test", getTest);
  server.begin();
}
