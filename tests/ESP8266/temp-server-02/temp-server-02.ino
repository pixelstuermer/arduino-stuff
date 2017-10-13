#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>


// WiFi and Server
const char* ssid = "ssid";
const char* password = "pw";
ESP8266WebServer server(80);

// OneWire and Temperature
OneWire oneWire(D2);
DallasTemperature ds18b20(&oneWire);


/*
 * Setup the ESP as a Server
 */
void setup() {
  // Serial
  Serial.begin(9600);
  Serial.println(">>> Setup Start");
  // WiFi
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println(">>> Setup WiFi (STA-Mode)");
  Serial.print(">>> SSID: ");
  Serial.println(ssid);
  Serial.print(">>> IP: ");
  Serial.println(WiFi.localIP());
  // Server
  server.on("/temp", getTemp);
  server.begin();
  Serial.println(">>> Setup Server");
  Serial.println(">>> Setup All Ready");
}


/*
 * Looping Method
 */
void loop() {
  server.handleClient();
}


/*
 * /temp
 */
 void getTemp() {
  float currentTemp = readTemp();
  server.send(200, "text/plain", "Schlafzimmer: " + String(currentTemp));
  Serial.println(">>> Temperature: " + String(currentTemp));
 }


/*
 * Read and return the Temperature
 */
float readTemp() {
  float temp;
  do {
    ds18b20.requestTemperatures();
    temp = ds18b20.getTempCByIndex(0);
  } while(temp==(85.0) || temp==(-127.0));
  return temp;
}
