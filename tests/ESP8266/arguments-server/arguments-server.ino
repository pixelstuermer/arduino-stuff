#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ssid";
const char* password = "pw";
ESP8266WebServer server(80);

const uint8_t BLUE = D5;

void setup() {
  Serial.begin(9600);
  setPins();
  setConnection();
  server.on("/led", handleLed);
  server.begin();
  Serial.println(">>> Ready");
}

void loop() {
  server.handleClient();
}

void handleLed() {
  String wish = server.arg("state");
  if(wish.equals("on")) {
    digitalWrite(BLUE, 1);
  } else if(wish.equals("off")) {
    digitalWrite(BLUE, 0);
  }
  server.send(200, "text/plain", String(digitalRead(BLUE)));
}

void setPins() {
  pinMode(BLUE, OUTPUT);
  digitalWrite(BLUE, 0);
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
