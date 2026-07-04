/******************************************************************************
 * Author: Kripa Maria [cite: 55, 248]
 * Date: July 2026 [cite: 55, 248]
 * Description: 4-key scale piano running scale chords and scale modulations[cite: 105, 108, 109].
 *****************************************************************************/
const int BTN_DO = 2; const int BTN_RE = 3; const int BTN_MI = 4; const int BTN_FA = 5;
const int BTN_TOGGLE = 6; const int BUZZER_PIN = 9;

bool minorScaleMode = false;

void setup() {
  pinMode(BTN_DO, INPUT_PULLUP); pinMode(BTN_RE, INPUT_PULLUP);
  pinMode(BTN_MI, INPUT_PULLUP); pinMode(BTN_FA, INPUT_PULLUP);
  pinMode(BTN_TOGGLE, INPUT_PULLUP); pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(BTN_TOGGLE) == LOW) {
    minorScaleMode = !minorScaleMode; // Mode shift [cite: 109]
    delay(300);
  }

  int activeKeys = 0;
  if (digitalRead(BTN_DO) == LOW) activeKeys++;
  if (digitalRead(BTN_RE) == LOW) activeKeys++;
  if (digitalRead(BTN_MI) == LOW) activeKeys++;
  if (digitalRead(BTN_FA) == LOW) activeKeys++;

  // Chord rule processing check [cite: 108]
  if (activeKeys >= 2) {
    tone(BUZZER_PIN, 392); // Play Sol chord substitute note [cite: 108]
  } 
  else if (digitalRead(BTN_DO) == LOW) {
    tone(BUZZER_PIN, minorScaleMode ? 247 : 262); // Do pitch selection [cite: 106]
  } 
  else if (digitalRead(BTN_RE) == LOW) {
    tone(BUZZER_PIN, minorScaleMode ? 277 : 294); // Re pitch selection [cite: 106]
  } 
  else if (digitalRead(BTN_MI) == LOW) {
    tone(BUZZER_PIN, minorScaleMode ? 311 : 330); // Mi pitch selection [cite: 106]
  } 
  else if (digitalRead(BTN_FA) == LOW) {
    tone(BUZZER_PIN, minorScaleMode ? 329 : 349); // Fa pitch selection [cite: 106]
  } 
  else {
    noTone(BUZZER_PIN); // Mute on silence bounds [cite: 107]
  }
}
