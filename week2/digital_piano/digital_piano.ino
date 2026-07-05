const int KEY_PINS[] = {2, 3, 4, 5};
const int BUZZER_PIN = 8;
const int NOTE_FREQS[] = {262, 294, 330, 349};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(KEY_PINS[i], INPUT_PULLUP);
  }
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  bool anyPressed = false;
  
  for (int i = 0; i < 4; i++) {
    if (digitalRead(KEY_PINS[i]) == LOW) {
      tone(BUZZER_PIN, NOTE_FREQS[i]);
      anyPressed = true;
      break;
    }
  }
  
  if (!anyPressed) {
    noTone(BUZZER_PIN);
  }
}
