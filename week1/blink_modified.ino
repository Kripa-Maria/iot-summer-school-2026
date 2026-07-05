void setup() {
  pinMode(13, OUTPUT);
}

void loop() {

  // Blink LED 3 times quickly
  for (int i = 0; i < 3; i++) {
    digitalWrite(13, HIGH);
    delay(200);

    digitalWrite(13, LOW);
    delay(200);
  }

  // Pause for 2 seconds
  delay(2000);
}
