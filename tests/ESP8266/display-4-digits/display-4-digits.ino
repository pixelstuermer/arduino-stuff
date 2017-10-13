#include <TM1637Display.h>
#define CLK D2
#define DIO D1

TM1637Display display(CLK, DIO);
int counter;

void setup() {
  Serial.begin(9600);
  display.setBrightness(7);
  counter = 0;
}

void loop() {
  display.showNumberDec(counter);
  Serial.println(String(counter));
  delay(100);
  counter++;
}
