// Pin Configuration Assignments
const int LDR_PIN  = A0;
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

// Non-blocking sampling timer tracking parameters
unsigned long prevLogMillis = 0;
const long logInterval      = 2000; // Log system metrics exactly every 2 seconds

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  
  // Print CSV Header row matching strict assignment guidelines
  Serial.println("timestamp_ms,distance_cm,light_intensity");
}

void loop() {
  unsigned long currentMillis = millis();

  // Non-blocking operational tracking window loop
  if (currentMillis - prevLogMillis >= logInterval) {
    prevLogMillis = currentMillis;

    // 1. Trigger and acquire Ultrasonic Distance metric
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    float distance = (duration * 0.034) / 2.0;

    // 2. Read LDR Ambient Light intensity metric
    int lightIntensity = analogRead(LDR_PIN);

    // 3. Output data packet via structured CSV layout string stream
    Serial.print(currentMillis);
    Serial.print(",");
    
    if (duration == 0) {
      Serial.print("0.0"); // Error buffer handler output
    } else {
      Serial.print(distance, 1);
    }
    
    Serial.print(",");
    Serial.println(lightIntensity);
  }
}
