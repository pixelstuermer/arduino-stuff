#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "ssid";
const char* password = "pw";
const uint8_t LED = D8;
const uint8_t TEMP = D4;

double currentTemp;
int currentState;

ESP8266WebServer server(80);
OneWire oneWire(TEMP);
DallasTemperature ds18b20(&oneWire);

void setup() {
  Serial.begin(9600);
  setPins();
  setConnection();
  server.on("/", handleRoot);
  server.on("/led", handleLed);
  server.on("/temp", handleTemp);
  server.begin();
  Serial.println(">>> Ready");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", createHtml());
}

void handleLed() {
  String state = server.arg("state");
  if(state.equals("on")) {
    digitalWrite(LED, 1);
    currentState = 1;
  } else if(state.equals("off")) {
    digitalWrite(LED, 0);
    currentState = 0;
  }
  server.send(200, "text/html", createHtml());
}

void handleTemp() {
  currentTemp = getTemp();
  server.send(200, "text/html", createHtml());
}

float getTemp() {
  float temp;
  do {
    ds18b20.requestTemperatures();
    temp = ds18b20.getTempCByIndex(0);
  } while(temp==(85.0) || temp==(-127.0));
  return temp;
}

String createHtml() {
  String switcher = "";
  String ledIcon = "";
  if(currentState == 1) {
    switcher = "off";
    ledIcon = "fui-check-circle";
  } else if(currentState == 0) {
    switcher = "on";
    ledIcon = "fui-cross-circle";
  }
  return "<html><head><meta name=\"viewport\" content=\"width=device-width; initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0, user-scalable=no\"><link href=\"http://designmodo.github.io/Flat-UI/dist/css/vendor/bootstrap/css/bootstrap.min.css\" rel=\"stylesheet\"><link href=\"http://designmodo.github.io/Flat-UI/dist/css/flat-ui.css\" rel=\"stylesheet\"><script src=\"http://designmodo.github.io/Flat-UI/dist/js/vendor/jquery.min.js\"></script><script src=\"http://designmodo.github.io/Flat-UI/dist/js/flat-ui.min.js\"></script><script src=\"http://designmodo.github.io/Flat-UI/docs/assets/js/application.js\"></script><style>body {background-color: #ECF0F1;} .outline {text-align: center; display: table; width: 100%; height: 100%; padding-top: 50px;} .inline {display: table-cell; vertical-align: top;} h1 {color: #34495e;} .btn-primary {background-color: #1abc9c; width: 200px; padding: 15px; margin: 10px;} [class*=\"fui-\"] {color: #ffffff;}</style></head><body><div class=\"outline\"><div class=\"inline\"><h1>LEDs</h1><div><a href=\"/led?state=" + switcher + "\" class=\"btn btn-lg btn-primary\">Blau <span class=\"" + ledIcon + "\" style=\"margin-left: 10px;\"></a></div><div><a href=\"/temp\" class=\"btn btn-lg btn-primary\">Temperatur: " + String(currentTemp) + "</span></a></div></div></div></body></html>";
}

void setPins() {
  pinMode(TEMP, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  currentTemp = getTemp();
  currentState = 0;
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
