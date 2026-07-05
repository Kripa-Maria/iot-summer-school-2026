#include <Servo.h>

// Pin Configuration Assignments
const int POT_PIN    = A0;
const int BUTTON_PIN = 2;
const int SERVO_PIN  = 6;

Servo myServo;

// Operational state machine variables
bool isAutomaticMode = false;
bool lastButtonState = HIGH;
int servoAngle       = 0;
int sweepDirection   = 1; // 1 = forward, -1 = reverse

// Non-blocking timers
unsigned long prevSweepMillis  = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // 50ms debouncing window filter
const int sweepSpeedInterval      = 15; // Lower = faster automatic sweep rate

void setup() {
  myServo.attach(SERVO_PIN);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Employs internal safety pullup configuration
  Serial.begin(9600);
  
  // Initialize baseline posture
  myServo.write(0);
  Serial.println("SYSTEM READY: Mode = Manual Control via Potentiometer");
}

void loop() {
  unsigned long currentMillis = millis();
  int reading = digitalRead(BUTTON_PIN);

  // 1. Debounce and validate pushbutton state transitions
  if (reading != lastButtonState) {
    lastDebounceTime = currentMillis;
  }

  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && lastButtonState == HIGH) {
      isAutomaticMode = !isAutomaticMode; // Invert functional flag
      Serial.print("MODE CHANGE: Shifting system state to ");
      Serial.println(isAutomaticMode ? "AUTOMATIC SWEEP" : "MANUAL DIAL");
    }
  }
  lastButtonState = reading;

  // 2. Execute operational loop tracking based on selected state mode
  if (isAutomaticMode) {
    // AUTOMATIC MODE: Smoothly sweep back and forth using non-blocking timers
    if (currentMillis - prevSweepMillis >= sweepSpeedInterval) {
      prevSweepMillis = currentMillis;
      
      servoAngle += sweepDirection;
      if (servoAngle >= 180) {
        servoAngle = 180;
        sweepDirection = -1; // Reverse trajectory direction
      } else if (servoAngle <= 0) {
        servoAngle = 0;
        sweepDirection = 1;  // Forward trajectory direction
      }
      myServo.write(servoAngle);
    }
  } else {
    // MANUAL MODE: Directly read the dial pot value and scale to degrees
    int potValue = analogRead(POT_PIN);
    int targetAngle = map(potValue, 0, 1023, 0, 180);
    
    // Low-pass stabilizer matrix to filter hardware sensor noise jitter
    if (abs(targetAngle - servoAngle) > 1) {
      servoAngle = targetAngle;
      myServo.write(servoAngle);
    }
  }
}
