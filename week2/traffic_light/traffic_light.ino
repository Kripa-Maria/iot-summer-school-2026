const int redLED = 12;
const int yellowLED = 11;
const int greenLED = 10;
const int buttonPin = 7;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void checkPedestrianButton(unsigned long duration) {
  unsigned long startMillis = millis();
  while (millis() - startMillis < duration) {
    if (digitalRead(buttonPin) == LOW) {
      Serial.print("[");
      Serial.print(millis());
      Serial.println(" ms] PEDESTRIAN OVERRIDE: Forcing RED Light (8s)");
      
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);
      delay(8000);
      
      Serial.print("[");
      Serial.print(millis());
      Serial.println(" ms] Pedestrian window cleared. Resuming normal loop.");
      return;
    }
  }
}

void loop() {
  Serial.print("[");
  Serial.print(millis());
  Serial.println(" ms] State: RED (5s)");
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  checkPedestrianButton(5000);

  Serial.print("[");
  Serial.print(millis());
  Serial.println(" ms] State: YELLOW (2s)");
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, LOW);
  checkPedestrianButton(2000);

  Serial.print("[");
  Serial.print(millis());
  Serial.println(" ms] State: GREEN (4s)");
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);
  checkPedestrianButton(4000);
}
