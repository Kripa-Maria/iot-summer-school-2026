/******************************************************************************
 * Author: Kripa Maria [cite: 55, 248]
 * Date: July 2026 [cite: 55, 248]
 * Description: Junction traffic controller with pedestrian override push button[cite: 101].
 *****************************************************************************/
const int RED_PIN = 10;
const int YEL_PIN = 11;
const int GRN_PIN = 12;
const int BTN_PIN = 7; // Pedestrian override pin requirement [cite: 101]

void setup() {
  pinMode(RED_PIN, OUTPUT); pinMode(YEL_PIN, OUTPUT); pinMode(GRN_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void changeState(String state, unsigned long duration) {
  Serial.print("["); Serial.print(millis()); Serial.print(" ms] State: "); Serial.println(state); [cite: 102]
  unsigned long start = millis();
  while (millis() - start < duration) {
    // Actively check for pedestrian interrupt button pull down [cite: 101]
    if (digitalRead(BTN_PIN) == LOW) {
      Serial.print("["); Serial.print(millis()); Serial.println(" ms] ALERT: Pedestrian Button Triggered!"); [cite: 102]
      digitalWrite(GRN_PIN, LOW); digitalWrite(YEL_PIN, LOW);
      digitalWrite(RED_PIN, HIGH);
      delay(8000); // Enforce strict 8-second safety latch window [cite: 101]
      return;
    }
  }
}

void loop() {
  // Standard loop operations sequence [cite: 101]
  digitalWrite(RED_PIN, HIGH); digitalWrite(YEL_PIN, LOW); digitalWrite(GRN_PIN, LOW);
  changeState("RED", 5000); [cite: 101]

  digitalWrite(RED_PIN, LOW); digitalWrite(YEL_PIN, HIGH); digitalWrite(GRN_PIN, LOW);
  changeState("YELLOW", 2000); [cite: 101]

  digitalWrite(RED_PIN, LOW); digitalWrite(YEL_PIN, LOW); digitalWrite(GRN_PIN, HIGH);
  changeState("GREEN", 4000); [cite: 101]
}
