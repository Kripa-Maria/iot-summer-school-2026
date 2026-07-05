const int in1=8, in2=9, ena=10, potPin=A0, btnDir=6, btnRun=7;
bool forward = true, running = false;
int lastDirState = HIGH, lastRunState = HIGH;

void setup() {
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT); pinMode(ena, OUTPUT);
  pinMode(btnDir, INPUT_PULLUP); pinMode(btnRun, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int dirState = digitalRead(btnDir);
  if (dirState == LOW && lastDirState == HIGH) { forward = !forward; delay(200); }
  lastDirState = dirState;

  int runState = digitalRead(btnRun);
  if (runState == LOW && lastRunState == HIGH) { running = !running; delay(200); }
  lastRunState = runState;

  int speedRaw = analogRead(potPin);
  int speedPWM = running ? map(speedRaw, 0, 1023, 0, 255) : 0;
  int speedPct = map(speedPWM, 0, 255, 0, 100);

  digitalWrite(in1, forward ? HIGH : LOW);
  digitalWrite(in2, forward ? LOW : HIGH);
  analogWrite(ena, speedPWM);

  Serial.print("Direction: "); Serial.print(forward ? "Forward" : "Reverse");
  Serial.print(" | Speed: "); Serial.print(speedPct); Serial.print("%");
  Serial.print(" | State: "); Serial.println(running ? "RUNNING" : "STOPPED");
  delay(300);
}
