/******************************************************************************
 * Author: Kripa Maria
 * Date: July 2026
 * Description: Versioned LED blink controller parsing analog potentiometer data 
 * to adjust hardware duty-cycle speeds. Includes threshold boundary safety logic.
 * Version: v1.4
 *****************************************************************************/
int blinkCount = 0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  
  // Bugfix Implementation: Enforce strict boundary threshold clamping 
  // to ensure smooth transition scaling even at maximum potentiometer limits.
  if (sensorValue > 1020) {
    sensorValue = 1023;
  }

  int blinkDelay = map(sensorValue, 0, 1023, 100, 2000);

  digitalWrite(13, HIGH);
  delay(blinkDelay);
  digitalWrite(13, LOW);
  delay(blinkDelay);
  
  blinkCount++;
  Serial.print("Blink count: ");
  Serial.println(blinkCount);
}
