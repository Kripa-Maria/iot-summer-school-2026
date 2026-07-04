const int EN_A = 5;
const int IN1  = 3;
const int IN2  = 4;
const int POT  = A0;
const int DIR_BTN  = 7;
const int STOP_BTN = 8;

bool active = true;
bool forward = true;

void setup() {
  pinMode(EN_A, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(DIR_BTN, INPUT_PULLUP); pinMode(STOP_BTN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(STOP_BTN) == LOW) { active = !active; delay(300); }
  if (digitalRead(DIR_BTN) == LOW) { forward = !forward; delay(300); }

  int pwm = map(analogRead(POT), 0, 1023, 0, 255);
  int pct = map(pwm, 0, 255, 0, 100);

  if (!active) {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); analogWrite(EN_A, 0);
    Serial.println("State: OFF | Speed: 0% | Dir: N/A");
  } else {
    digitalWrite(IN1, forward ? HIGH : LOW);
    digitalWrite(IN2, forward ? LOW : HIGH);
    analogWrite(EN_A, pwm);
    
    Serial.print("State: RUNNING | Speed: "); Serial.print(pct);
    Serial.print("% | Dir: "); Serial.println(forward ? "Forward" : "Reverse");
  }
  delay(100);
}
