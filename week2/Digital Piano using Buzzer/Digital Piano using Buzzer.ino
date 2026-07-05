const int btnDo=2, btnRe=3, btnMi=4, btnFa=5, btnMode=6, buzzer=8;
bool minorMode = false;
int lastModeState = HIGH;

void setup() {
  pinMode(btnDo, INPUT_PULLUP); pinMode(btnRe, INPUT_PULLUP);
  pinMode(btnMi, INPUT_PULLUP); pinMode(btnFa, INPUT_PULLUP);
  pinMode(btnMode, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int modeState = digitalRead(btnMode);
  if (modeState == LOW && lastModeState == HIGH) {
    minorMode = !minorMode;
    Serial.println(minorMode ? "Mode: MINOR" : "Mode: MAJOR");
    delay(200); // debounce
  }
  lastModeState = modeState;

  bool doPressed = digitalRead(btnDo) == LOW;
  bool rePressed = digitalRead(btnRe) == LOW;
  bool miPressed = digitalRead(btnMi) == LOW;
  bool faPressed = digitalRead(btnFa) == LOW;

  int pressedCount = doPressed + rePressed + miPressed + faPressed;

  if (pressedCount >= 2) {
    tone(buzzer, minorMode ? 370 : 392); // Sol, slightly flat for "minor" flavor
  } else if (doPressed) {
    tone(buzzer, minorMode ? 247 : 262); // Do
  } else if (rePressed) {
    tone(buzzer, minorMode ? 277 : 294); // Re
  } else if (miPressed) {
    tone(buzzer, minorMode ? 311 : 330); // Mi
  } else if (faPressed) {
    tone(buzzer, 349); // Fa
  } else {
    noTone(buzzer);
  }
}
