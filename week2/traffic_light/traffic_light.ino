/******************************************************************************
 * Author: Kripa Maria
 * Date: July 2026
 * Description: Q14 Traffic Light Controller with non-blocking emergency 
 * button poll routine to override state tracking.
 * Version: v1.0
 *****************************************************************************/

// Pin definitions matching your Tinkercad configuration
const int redLED = 12;
const int yellowLED = 11;
const int greenLED = 10;
const int buttonPin = 7;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  // Set up button with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  
  Serial.begin(9600);
  Serial.println("System Boot: Traffic Light Sequence Active.");
}

// Non-blocking custom delay loop that monitors the button pin
void cycleDelay(unsigned long duration) {
  unsigned long startTimestamp = millis();
  
  while (millis() - startTimestamp < duration) {
    // If emergency button is pressed (LOW state)
    if (digitalRead(buttonPin) == LOW) {
      Serial.println("EMERGENCY - Force Red for safety!");
      
      // Force immediate override visual states
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);
      
      // Hold emergency red light alert state for 5 seconds
      delay(5000); 
      
      Serial.println("Emergency cleared. Resuming cycle...");
      return;
    }
  }
}

void loop() {
  // --- RED LED CYCLE (5s) ---
  Serial.println("[0 ms] State Transition -> RED (5s)");
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  cycleDelay(5000);

  // --- YELLOW LED CYCLE (2s) ---
  Serial.println("[5000 ms] State Transition -> YELLOW (2s)");
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, LOW);
  cycleDelay(2000);

  // --- GREEN LED CYCLE (4s) ---
  Serial.println("[7000 ms] State Transition -> GREEN (4s)");
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);
  cycleDelay(4000);
}
