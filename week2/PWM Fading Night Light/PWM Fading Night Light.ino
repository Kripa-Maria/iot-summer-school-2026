/******************************************************************************
 * Author: Kripa Maria [cite: 55, 248]
 * Date: July 2026 [cite: 55, 248]
 * Description: Variable PWM cadence pulse modulation driving light fading configurations[cite: 124, 125, 126].
 *****************************************************************************/
const int LAMP_LED_PIN = 3;
const int BTN_MODE_PIN = 2;

int currentMode = 0; // 0: Slow Breathe, 1: Fast Pulse, 2: SOS Mode [cite: 126]
unsigned long markerTimer = 0;

void setup() {
  pinMode(LAMP_LED_PIN, OUTPUT);
  pinMode(BTN_MODE_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Current Active Mode: Slow Breathing"); [cite: 127]
}

void triggerSOSPattern() {
  // SOS Morse Code timing profile sequences [cite: 126]
  int schedule[] = {150, 150, 150, 450, 450, 450, 150, 150, 150};
  for (int i = 0; i < 9; i++) {
    if (digitalRead(BTN_MODE_PIN) == LOW) return; // Prompt break on mode shift press
    analogWrite(LAMP_LED_PIN, 255); delay(schedule[i]);
    analogWrite(LAMP_LED_PIN, 0);   delay(200);
  }
  delay(1000);
}

void loop() {
  if (digitalRead(BTN_MODE_PIN) == LOW) {
    currentMode = (currentMode + 1) % 3; // Shift structural pointer mode [cite: 126]
    delay(300);
    if (currentMode == 0) Serial.println("Current Active Mode: Slow Breathing"); [cite: 127]
    if (currentMode == 1) Serial.println("Current Active Mode: Fast Pulse"); [cite: 127]
    if (currentMode == 2) Serial.println("Current Active Mode: SOS Emergency Matrix Pattern"); [cite: 127]
  }

  if (currentMode == 0) { // Slow breathing mode fading loop execution (3s cycle) [cite: 125, 126]
    float val = (exp(sin(millis() / 3000.0 * PI)) - 0.36787944) * 108.0;
    analogWrite(LAMP_LED_PIN, val);
  } 
  else if (currentMode == 1) { // Fast pulse loop execution (0.5s cycle) [cite: 126]
    float val = (exp(sin(millis() / 500.0 * PI)) - 0.36787944) * 108.0;
    analogWrite(LAMP_LED_PIN, val);
  } 
  else if (currentMode == 2) {
    triggerSOSPattern(); [cite: 126]
  }
}
