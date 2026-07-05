const int potPin = A0, relayPin = 8, btn = 7;
bool relayOn = false, manualOverride = false;
int lastBtnState = HIGH;

float readSimulatedTemp() {
  int raw = analogRead(potPin);           // 0–1023
  return map(raw, 0, 1023, 0, 500) / 10.0; // maps to 0.0–50.0 °C
}

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int btnState = digitalRead(btn);
  if (btnState == LOW && lastBtnState == HIGH) {
    manualOverride = !manualOverride;
    Serial.println(manualOverride ? "Manual override ON" : "Manual override OFF, resuming auto");
    delay(200);
  }
  lastBtnState = btnState;

  float temp = readSimulatedTemp();

  if (!manualOverride) {
    if (!relayOn && temp > 32) { relayOn = true; }
    else if (relayOn && temp < 28) { relayOn = false; }
  }

  digitalWrite(relayPin, relayOn ? HIGH : LOW);
  Serial.print("Temp (pot): "); Serial.print(temp);
  Serial.print(" C | Relay: "); Serial.println(relayOn ? "ON" : "OFF");
  delay(500);
}
