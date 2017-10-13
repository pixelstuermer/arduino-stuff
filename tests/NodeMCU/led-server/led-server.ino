#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ssid";
const char* password = "pw";
ESP8266WebServer server(80);

const uint8_t YELLOW = D3;
const uint8_t RED = D4;

void setup() {
  Serial.begin(9600);
  setPins();
  setConnection();
  server.on("/", handleRoot);
  server.on("/red", handleRed);
  server.on("/yellow", handleYellow);
  server.begin();
  Serial.println(">>> Ready");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", getHtml(digitalRead(RED), digitalRead(YELLOW)));
}

void handleRed() {
  if(digitalRead(RED) == 0) {
    digitalWrite(RED, 1);
  } else {
    digitalWrite(RED, 0);
  }
  server.send(200, "text/html", getHtml(digitalRead(RED), digitalRead(YELLOW)));
}

void handleYellow() {
  if(digitalRead(YELLOW) == 0) {
    digitalWrite(YELLOW, 1);
  } else {
    digitalWrite(YELLOW, 0);
  }
  server.send(200, "text/html", getHtml(digitalRead(RED), digitalRead(YELLOW)));
}

void setPins() {
  pinMode(YELLOW, OUTPUT);
  digitalWrite(YELLOW, 0);
  pinMode(RED, OUTPUT);
  digitalWrite(RED, 0);
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

String getHtml(int red, int yellow) {
  String redBG = "grey";
  if(red == 0) {
    redBG = "red";
  } else {
    redBG = "green";
  }
  String yellowBG = "grey";
  if(yellow == 0) {
    yellowBG = "red";
  } else {
    yellowBG = "green";
  }
  return "<html><body><div style=\"height: 100%; width: 100%\"><div style=\"height: 50%; width: 100%\"><a href=\"/red\"><button type=\"button\" style=\"width: 100%; height: 100%; border-radius: 10px; background-color: " + redBG + "\">RED LED</button></a></div><div style=\"height: 50%; width: 100%\"><a href=\"/yellow\"><button type=\"button\" style=\"width: 100%; height: 100%; border-radius: 10px; background-color: " + yellowBG + "\">YELLOW LED</button></a></div></div></body></html>";
}
