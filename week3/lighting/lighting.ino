const int LDR_PIN = A1; const int PIR_PIN = 2; const int PWM_LAMP = 3; 
unsigned long trackingTimer = 0; bool motionTracked = false;

void setup() {
  pinMode(PIR_PIN, INPUT); pinMode(PWM_LAMP, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (analogRead(LDR_PIN) < 300) { 
    if (digitalRead(PIR_PIN) == HIGH) {
      analogWrite(PWM_LAMP, 255); trackingTimer = millis(); motionTracked = true;
    } else if (motionTracked && (millis() - trackingTimer > 30000)) {
      analogWrite(PWM_LAMP, 51); motionTracked = false;
    }
  } else {
    analogWrite(PWM_LAMP, 0); motionTracked = false;
  }
  delay(100);
}
