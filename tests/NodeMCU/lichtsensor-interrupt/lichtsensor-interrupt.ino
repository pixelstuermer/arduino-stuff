void setup() {
  setPins();
  attachInterrupt(D6, togglePin, CHANGE);
}

void loop() {
}

void setPins() {
  pinMode(D6, INPUT);
  pinMode(D2, OUTPUT);
}

void togglePin() {
  detachInterrupt(D4);
  if(digitalRead(D2)==1) {
    digitalWrite(D2, 0);
  } else {
    digitalWrite(D2, 1);
  }
  delay(200);
  attachInterrupt(D6, togglePin, CHANGE);
}
