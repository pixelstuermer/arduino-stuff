#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ssid";
const char* password = "pw";
int sleeper = 300000; // 5 min

void setup() {
  setPins();
  setConnection();
}

void loop() {
  if(digitalRead(D7) == 0) {
    sendPush();
  } else {
    // NOP
  }
  delay(300000);
}

void sendPush() {  
  HTTPClient http;
  http.begin("http://api.pushover.net/1/messages.json");
  http.POST("token=token&user=user&title=NodeMCU&message=Licht+ist+an!");
  http.end();
}

void setPins() {
  digitalWrite(LED_BUILTIN, 0);
  pinMode(D7, INPUT);
}

void setConnection() {
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
