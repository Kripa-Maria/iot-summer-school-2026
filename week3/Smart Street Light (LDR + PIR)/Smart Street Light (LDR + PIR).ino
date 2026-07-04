const int LDR_PIN = A1; const int PIR_PIN = 2; const int PWM_LAMP = 3; 
unsigned long lightTimer = 0; bool motion = false;
void setup() { pinMode(PIR_PIN, INPUT); pinMode(PWM_LAMP, OUTPUT); }
void loop() {
  if (analogRead(LDR_PIN) < 300) { 
    if (digitalRead(PIR_PIN) == HIGH) { analogWrite(PWM_LAMP, 255); lightTimer = millis(); motion = true; }
    else if (motion && (millis() - lightTimer > 30000)) { analogWrite(PWM_LAMP, 51); motion = false; }
  } else { analogWrite(PWM_LAMP, 0); motion = false; }
  delay(100);
}
