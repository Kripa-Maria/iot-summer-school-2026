const int TRIG_PIN = 6; const int ECHO_PIN = 7;
const int RED_LED = 9; const int YEL_LED = 10; const int GRN_LED = 11; const int BUZZER = 5;
unsigned long prevAlert = 0; unsigned long lastRead = 0; bool buzzState = false;
void setup() {
  pinMode(TRIG_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);
  pinMode(RED_LED, OUTPUT); pinMode(YEL_LED, OUTPUT); pinMode(GRN_LED, OUTPUT); pinMode(BUZZER, OUTPUT);
}
void loop() {
  if (millis() - lastRead >= 100) {
    lastRead = millis();
    digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2); digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10); digitalWrite(TRIG_PIN, LOW);
    long distance = (pulseIn(ECHO_PIN, HIGH) * 0.034) / 2;
    digitalWrite(GRN_LED, LOW); digitalWrite(YEL_LED, LOW); digitalWrite(RED_LED, LOW);
    if (distance > 50) { digitalWrite(GRN_LED, HIGH); digitalWrite(BUZZER, LOW); }
    else if (distance >= 20) { digitalWrite(YEL_LED, HIGH); if(millis()-prevAlert>500){prevAlert=millis(); buzzState=!buzzState; digitalWrite(BUZZER, buzzState);} }
    else if (distance >= 10) { digitalWrite(RED_LED, HIGH); if(millis()-prevAlert>200){prevAlert=millis(); buzzState=!buzzState; digitalWrite(BUZZER, buzzState);} }
    else { digitalWrite(GRN_LED, HIGH); digitalWrite(YEL_LED, HIGH); digitalWrite(RED_LED, HIGH); digitalWrite(BUZZER, HIGH); }
  }
}
