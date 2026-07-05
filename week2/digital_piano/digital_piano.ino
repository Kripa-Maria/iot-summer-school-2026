const int KEY_PINS[] = {2, 3, 4, 5};
const int BUZZER_PIN = 8;
const int NOTE_FREQS[] = {262, 294, 330, 349};
const int NOTE_SOL = 392;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(KEY_PINS[i], INPUT_PULLUP);
  }
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int pressCount = 0;
  int lastPressedIndex = -1;
  
  for (int i = 0; i < 4; i++) {
    if (digitalRead(KEY_PINS[i]) == LOW) {
      pressCount++;
      lastPressedIndex = i;
    }
  }
  
  if (pressCount > 1) {
    tone(BUZZER_PIN, NOTE_SOL);
  } else if (pressCount == 1) {
    tone(BUZZER_PIN, NOTE_FREQS[lastPressedIndex]);
  } else {
    noTone(BUZZER_PIN);
  }
}
