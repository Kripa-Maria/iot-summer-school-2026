const int ledPin = 9, btn = 7;
int mode = 0; // 0=slow breathing, 1=fast pulse, 2=SOS
int lastBtnState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Mode: Slow Breathing");
}

void breathe(int cycleMs) {
  int steps = 100;
  for (int i = 0; i < steps; i++) {
    if (checkModeChange()) return;
    analogWrite(ledPin, map(i, 0, steps, 0, 255));
    delay(cycleMs / (2 * steps));
  }
  for (int i = steps; i >= 0; i--) {
    if (checkModeChange()) return;
    analogWrite(ledPin, map(i, 0, steps, 0, 255));
    delay(cycleMs / (2 * steps));
  }
}

void sos() {
  int dot = 200, dash = 600, gap = 200;
  int pattern[] = {dot, dot, dot, dash, dash, dash, dot, dot, dot};
  for (int i = 0; i < 9; i++) {
    if (checkModeChange()) return;
    analogWrite(ledPin, 255); delay(pattern[i]);
    analogWrite(ledPin, 0); delay(gap);
  }
  delay(1000);
}

bool checkModeChange() {
  int state = digitalRead(btn);
  if (state == LOW && lastBtnState == HIGH) {
    mode = (mode + 1) % 3;
    Serial.println(mode == 0 ? "Mode: Slow Breathing" : mode == 1 ? "Mode: Fast Pulse" : "Mode: SOS");
    lastBtnState = state;
    delay(200);
    return true;
  }
  lastBtnState = state;
  return false;
}

void loop() {
  checkModeChange();
  if (mode == 0) breathe(3000);
  else if (mode == 1) breathe(500);
  else sos();
}
