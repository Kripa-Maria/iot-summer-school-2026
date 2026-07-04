/******************************************************************************
 * Author: Kripa Maria
 * Date: July 2026
 * Description: Non-blocking ultrasonic parking alert module.
 *****************************************************************************/
const int TRIG_PIN = 6;
const int ECHO_PIN = 7;
const int RED_LED  = 9;
const int YEL_LED  = 10;
const int GRN_LED  = 11;
const int BUZZER   = 5;

unsigned long previousAlertTime = 0;
unsigned long lastSensorTime = 0;
const long sensorInterval = 100; // Sample data every 100ms
bool buzzerState = false;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YEL_LED, OUTPUT);
  pinMode(GRN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return (duration * 0.034) / 2;
}

void triggerBeep(int rateMs) {
  if (millis() - previousAlertTime >= rateMs) {
    previousAlertTime = millis();
    buzzerState = !buzzerState;
    digitalWrite(BUZZER, buzzerState ? HIGH : LOW);
  }
}

void loop() {
  // Non-blocking sensory loop processing standard
  if (millis() - lastSensorTime >= sensorInterval) {
    lastSensorTime = millis();
    long distance = getDistance();

    digitalWrite(GRN_LED, LOW); digitalWrite(YEL_LED, LOW); digitalWrite(RED_LED, LOW);

    if (distance > 50) {
      digitalWrite(GRN_LED, HIGH);
      digitalWrite(BUZZER, LOW);
      Serial.println("SAFE");
    } 
    else if (distance >= 20 && distance <= 50) {
      digitalWrite(YEL_LED, HIGH);
      triggerBeep(500);
    } 
    else if (distance >= 10 && distance < 20) {
      digitalWrite(RED_LED, HIGH);
      triggerBeep(200);
    } 
    else { // Distance < 10cm bounds
      digitalWrite(GRN_LED, HIGH);
      digitalWrite(YEL_LED, HIGH);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(BUZZER, HIGH); // Continuous tone mapping
    }
  }
}
