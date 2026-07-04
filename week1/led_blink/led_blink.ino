/*
 * Author: Kripa-Maria
 * Date: July 2026
 * Description: Potentiometer controlled variable LED blinking mechanism.
 */

int blinkCount = 0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int sensorVal = analogRead(A0);
  
  digitalWrite(13, HIGH); delay(sensorVal);
  digitalWrite(13, LOW);  delay(sensorVal);
  
  blinkCount++;
  Serial.print("Blink count: ");
  Serial.println(blinkCount);
}
