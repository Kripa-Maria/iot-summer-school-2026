/*
 * Modified 
 * Added descriptive comments for readability.
 */
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  // Blink the LED 3 times fast
  for(int i = 0; i < 3; i++) {
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
  }
  // Pause cycle for exactly 2 seconds
  delay(2000);
}
