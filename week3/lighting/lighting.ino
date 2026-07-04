/******************************************************************************
 * Author: Kripa Maria
 * Date: July 2026
 * Description: Street lamp dimming framework utilizing motion checks.
 *****************************************************************************/
const int LDR_PIN = A1;
const int PIR_PIN = 2;
const int PWM_LAMP = 3; 

unsigned long trackingTimer = 0;
bool motionTracked = false;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(PWM_LAMP, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lux = analogRead(LDR_PIN);
  int motion = digitalRead(PIR_PIN);

  if (lux < 300) { // Ambient Night condition
    if (motion == HIGH) {
      analogWrite(PWM_LAMP, 255); // 100% full capacity output
      trackingTimer = millis();
      motionTracked = true;
      Serial.println("[HH:MM:SS] EVENT: Motion detected! Lamp set to full power.");
    } 
    else if (motionTracked && (millis() - trackingTimer > 30000)) {
      analogWrite(PWM_LAMP, 51); // Dim down directly to 20% PWM output limits
      motionTracked = false;
      Serial.println("[HH:MM:SS] EVENT: Timeout reached. Dimming lamp to 20%.");
    }
  } else { // Ambient Daylight condition
    analogWrite(PWM_LAMP, 0); // Complete load cutoff
    motionTracked = false;
  }
  delay(100);
}
