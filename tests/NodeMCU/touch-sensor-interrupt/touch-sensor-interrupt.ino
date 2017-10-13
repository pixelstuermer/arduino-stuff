void setup() {
  setPins();
  Serial.begin(9600);
  attachInterrupt(D1, togglePin, RISING);
}

void loop() {
}

void setPins() {
  pinMode(D1, INPUT);
}

void togglePin() {
  detachInterrupt(D1);
  Serial.println("Press registerred!");
  delay(1000);
  attachInterrupt(D1, togglePin, RISING);
}
