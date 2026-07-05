// Pin Assignments
const int TRIG_PIN   = 9;
const int ECHO_PIN   = 10;
const int YELLOW_LED = 5;
const int RED_LED    = 6;
const int BUZZER_PIN = 7;

unsigned long prevBlinkMillis = 0;
unsigned long prevPingMillis  = 0;
const long pingInterval       = 60;
bool alertState               = false;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(TRIG_PIN, LOW); // ensure known starting state
  delay(50);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - prevPingMillis >= pingInterval) {
    prevPingMillis = currentMillis;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    float distance = (duration * 0.034) / 2.0;

    // --- DEBUG LINE: remove once confirmed working ---
    Serial.print("raw duration="); Serial.print(duration);
    Serial.print(" us | distance="); Serial.print(distance);
    Serial.println(" cm");

    if (duration == 0) {
      // No echo at all — this is a wiring/placement issue, NOT a "safe" reading
      Serial.println("NO ECHO - check Trig/Echo wiring or move obstacle closer in simulator");
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(RED_LED, LOW);
      noTone(BUZZER_PIN);
    }
    else if (distance > 50.0) {
      Serial.println("SAFE");
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(RED_LED, LOW);
      noTone(BUZZER_PIN);
    }
    else if (distance >= 20.0 && distance <= 50.0) {
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      handleBeep(currentMillis, 500);
    }
    else if (distance >= 10.0 && distance < 20.0) {
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      handleBeep(currentMillis, 200);
    }
    else if (distance < 10.0) {
      handleRapidAlert(currentMillis);
    }
  }
}

void handleBeep(unsigned long currentMillis, long interval) {
  if (currentMillis - prevBlinkMillis >= interval) {
    prevBlinkMillis = currentMillis;
    alertState = !alertState;
    if (alertState) tone(BUZZER_PIN, 1000);
    else noTone(BUZZER_PIN);
  }
}

void handleRapidAlert(unsigned long currentMillis) {
  tone(BUZZER_PIN, 1000);
  if (currentMillis - prevBlinkMillis >= 100) {
    prevBlinkMillis = currentMillis;
    alertState = !alertState;
    digitalWrite(YELLOW_LED, alertState);
    digitalWrite(RED_LED, !alertState);
  }
}
