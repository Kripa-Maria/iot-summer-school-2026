// Pin Assignments
const int LDR_PIN    = A0;
const int PIR_PIN    = 2;
const int STREET_LED = 3; // PWM pin

// Calibration Thresholds
const int LDR_DARK_THRESHOLD = 400;

unsigned long motionStartMillis = 0;
bool motionActive = false;

// Track state ourselves instead of reading it back from the PWM pin
enum LightState { LIGHT_OFF, LIGHT_DIM, LIGHT_BRIGHT };
LightState currentState = LIGHT_OFF;
void setLight(LightState newState);
void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(STREET_LED, OUTPUT);
  Serial.begin(9600);
}

void logEvent(String msg) {
  unsigned long s = millis() / 1000;
  int hh = s / 3600, mm = (s % 3600) / 60, ss = s % 60;
  Serial.print("[");
  if (hh < 10) Serial.print("0"); Serial.print(hh); Serial.print(":");
  if (mm < 10) Serial.print("0"); Serial.print(mm); Serial.print(":");
  if (ss < 10) Serial.print("0"); Serial.print(ss);
  Serial.print("] "); Serial.println(msg);
}

void setLight(LightState newState) {
  if (newState == currentState) return; // avoid spamming Serial every loop
  currentState = newState;
  switch (newState) {
    case LIGHT_OFF:    analogWrite(STREET_LED, 0);   logEvent("DAYLIGHT: Street light OFF"); break;
    case LIGHT_DIM:    analogWrite(STREET_LED, 51);  logEvent("NIGHT MODE: Dimmed to 20% (idle)"); break;
    case LIGHT_BRIGHT: analogWrite(STREET_LED, 255); logEvent("NIGHT MODE: Motion detected! 100% brightness"); break;
  }
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  bool motionDetected = digitalRead(PIR_PIN);
  bool isDark = ldrValue < LDR_DARK_THRESHOLD;

  if (!isDark) {
    setLight(LIGHT_OFF);
    motionActive = false;
  } else {
    // It's dark
    if (motionDetected) {
      motionActive = true;
      motionStartMillis = millis();
      setLight(LIGHT_BRIGHT);
    } else if (motionActive && (millis() - motionStartMillis >= 30000)) {
      motionActive = false;
      setLight(LIGHT_DIM);
    } else if (currentState == LIGHT_OFF) {
      // Just became dark, no motion yet — go straight to dim baseline
      setLight(LIGHT_DIM);
    }
  }

  delay(100);
}
