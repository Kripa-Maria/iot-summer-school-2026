#include <Servo.h>
Servo myServo;
const int POT_PIN = A0; const int BTN_PIN = 2; const int SERVO_PIN = 9;
void setup() { myServo.attach(SERVO_PIN); pinMode(BTN_PIN, INPUT_PULLUP); }
void loop() {
  if (digitalRead(BTN_PIN) == LOW) {
    for (int a = 0; a <= 180; a++) { myServo.write(a); delay(15); }
    for (int a = 180; a >= 0; a--) { myServo.write(a); delay(15); }
    return;
  }
  myServo.write(map(analogRead(POT_PIN), 0, 1023, 0, 180));
  delay(50);
}
