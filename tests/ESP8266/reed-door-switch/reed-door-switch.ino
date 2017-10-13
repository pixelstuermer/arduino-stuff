void setup() {
  Serial.begin(9600);
  setPins();
  attachInterrupt(D1, toggleReedSwitch, FALLING);
  Serial.println(">>> Start");
}

void loop() {
}

void setPins() {
  // D1 Reed Switch Pin
  pinMode(D1, INPUT);
  Serial.println(">>> Pin Setup");
}

void toggleReedSwitch() {
  detachInterrupt(D1);
  Serial.println(">>> ReedSwitch Off");
  delay(200);
  attachInterrupt(D1, toggleReedSwitch, FALLING);
}
