const int KEY_PINS[] = {2, 3, 4, 5};
const int TOGGLE_PIN = 6;
const int BUZZER_PIN = 8;

const int MAJOR_FREQS[] = {262, 294, 330, 349}; // Do, Re, Mi, Fa
const int MINOR_FREQS[] = {262, 294, 311, 349}; // Do, Re, Me (Flatted), Fa
const int NOTE_SOL = 392;

bool isMinorMode = false;
bool lastToggleState = HIGH;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(KEY_PINS[i], INPUT_PULLUP);
  }
  pinMode(TOGGLE_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  bool currentToggleState = digitalRead(TOGGLE_PIN);
  if (lastToggleState == HIGH && currentToggleState == LOW) {
    delay(50);
    isMinorMode = !isMinorMode;
    while(digitalRead(TOGGLE_PIN) == LOW);
  }
  lastToggleState = currentToggleState;

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
    int activeFreq = isMinorMode ? MINOR_FREQS[lastPressedIndex] : MAJOR_FREQS[lastPressedIndex];
    tone(BUZZER_PIN, activeFreq);
  } else {
    noTone(BUZZER_PIN);
  }
}
