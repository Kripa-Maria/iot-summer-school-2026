const int MQ2_PIN       = A0;
const int FLAME_DO_PIN  = 7;
const int FLAME_AO_PIN  = A1;
const int GREEN_LED     = 10;
const int YELLOW_LED    = 11;
const int RED_LED       = 12;
const int BUZZER        = 9;

enum SystemState { SAFE, WARNING, DANGER };
SystemState currentState = SAFE;

unsigned long lastBeepTime = 0;
unsigned long lastLogTime  = 0;

void setup() {
  Serial.begin(9600);
  pinMode(FLAME_DO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("MQ-2 warming up (2 minutes)...");
  unsigned long warmupStart = millis();
  while (millis() - warmupStart < 120000UL) {
    digitalWrite(YELLOW_LED, (millis() / 500) % 2); // blink while warming up
  }
  digitalWrite(YELLOW_LED, LOW);
  Serial.println("Warm-up complete. Monitoring started.");
}

void setLEDs(SystemState state) {
  digitalWrite(GREEN_LED,  state == SAFE);
  digitalWrite(YELLOW_LED, state == WARNING);
  digitalWrite(RED_LED,    state == DANGER);
}

void updateBuzzer(SystemState state) {
  unsigned long now = millis();
  if (state == SAFE) {
    digitalWrite(BUZZER, LOW);
  } else if (state == WARNING) {
    if (now - lastBeepTime > 1000) { // 1 beep per second
      tone(BUZZER, 1000, 150);
      lastBeepTime = now;
    }
  } else { // DANGER
    digitalWrite(BUZZER, HIGH); // continuous alarm
  }
}

void loop() {
  int gasRaw     = analogRead(MQ2_PIN);
  int gasPercent = map(gasRaw, 0, 1023, 0, 100);
  bool flameDetected = (digitalRead(FLAME_DO_PIN) == LOW); // active-low

  if (gasPercent > 60 || flameDetected) currentState = DANGER;
  else if (gasPercent > 30)             currentState = WARNING;
  else                                  currentState = SAFE;

  setLEDs(currentState);
  updateBuzzer(currentState);

  if (millis() - lastLogTime > 1000) {
    Serial.print("GAS: "); Serial.print(gasPercent); Serial.print("% | FLAME: ");
    Serial.print(flameDetected ? "DETECTED" : "NONE"); Serial.print(" | STATUS: ");
    Serial.println(currentState == SAFE ? "SAFE" : currentState == WARNING ? "WARNING" : "DANGER");
    lastLogTime = millis();
  }
}
