// Pin Configuration Assignments
const int TMP36_PIN  = A0;
const int RED_LED    = 12;
const int GREEN_LED  = 11;

// Threshold Operational Parameters
const float TEMP_THRESHOLD_C = 35.0;

// Non-blocking sampling timer parameters
unsigned long prevSampleMillis = 0;
const long sampleInterval      = 2000; // Sample metrics exactly every 2 seconds

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("SYSTEM READY: Environmental Monitoring Station Online.");
}

void loop() {
  unsigned long currentMillis = millis();

  // Non-blocking operational tracking window loop
  if (currentMillis - prevSampleMillis >= sampleInterval) {
    prevSampleMillis = currentMillis;

    // 1. Acquire raw analog data voltage metric
    int rawADC = analogRead(TMP36_PIN);
    float voltage = rawADC * (5.0 / 1023.0);

    // 2. Linear conversion formulas for the TMP36 sensor scaling
    float tempC = (voltage - 0.5) * 100.0;

    // 3. Evaluate threshold rules and trigger indicator matrix
    if (tempC >= TEMP_THRESHOLD_C) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      Serial.print("[ALERT] High Temp Detected: ");
    } else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      Serial.print("[NORMAL] Temperature: ");
    }
    
    Serial.print(tempC, 1);
    Serial.println(" C");
  }
}
