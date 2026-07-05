/******************************************************************************
 * Author: Kripa Maria
 * Date: July 2026
 * Description: Q14 Traffic Light Controller with non-blocking emergency 
 * button poll routine to override state tracking.
 * Version: v1.0
 *****************************************************************************/


const int red = 2, yellow = 3, green = 4, btn = 7;
unsigned long stateStart = 0;
int state = 0; // 0=RED,1=YELLOW,2=GREEN
bool pedestrianOverride = false;

void setup() {
  pinMode(red, OUTPUT); pinMode(yellow, OUTPUT); pinMode(green, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600);
  stateStart = millis();
  setLights();
}

void setLights() {
  digitalWrite(red, state == 0);
  digitalWrite(yellow, state == 1);
  digitalWrite(green, state == 2);
  Serial.print("Time: "); Serial.print(millis());
  Serial.print(" ms | State: ");
  Serial.println(state == 0 ? "RED" : state == 1 ? "YELLOW" : "GREEN");
}

void loop() {
  unsigned long elapsed = millis() - stateStart;

  if (digitalRead(btn) == LOW && !pedestrianOverride) {
    pedestrianOverride = true;
    state = 0;
    stateStart = millis();
    setLights();
    return;
  }

  if (pedestrianOverride) {
    if (elapsed >= 8000) { pedestrianOverride = false; stateStart = millis(); }
    return;
  }

  long duration = (state == 0) ? 5000 : (state == 1) ? 2000 : 4000;
  if (elapsed >= duration) {
    state = (state + 1) % 3;
    stateStart = millis();
    setLights();
  }
}
