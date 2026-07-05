int blinkCount = 0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  // Map analog values (0-1023) to a comfortable delay range (100ms - 2000ms)
  int blinkDelay = map(sensorValue, 0, 1023, 100, 2000);

  digitalWrite(13, HIGH);
  delay(blinkDelay);
  digitalWrite(13, LOW);
  delay(blinkDelay);
  
  blinkCount++;
  Serial.print("Blink count: ");
  Serial.println(blinkCount);
}
