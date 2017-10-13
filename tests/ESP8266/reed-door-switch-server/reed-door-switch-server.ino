#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ssid";
const char* password = "pw";
ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  setPins();
  setConnection();
  setServer();
  Serial.println(">>> Ready");
}

void loop() {
  server.handleClient();
}

void getReedState() {
  int currentReedState = checkReed();
  server.send(200, "text/plain", "Reed: " + String(currentReedState));
  Serial.println(">>> Reed: " + String(currentReedState));
}

void getTest() {
  server.send(200, "text/plain", "ESP01: Test");
  Serial.println(">>> Test");
}

int checkReed() {
  int current = digitalRead(2);
  if(current==1) {
    setPins();
  }
  return current;
}

void setPins() {
  pinMode(2, OUTPUT);
  pinMode(2, 0);
  pinMode(2, INPUT);
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
  server.on("/reed", getReedState);
  server.on("/test", getTest);
  server.begin();
}
