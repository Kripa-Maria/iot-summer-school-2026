/******************************************************************************
 * Author: Kripa Maria [cite: 55, 248]
 * Date: July 2026 [cite: 55, 248]
 * Description: Serial parser terminal supporting input status validation checks[cite: 112, 123].
 *****************************************************************************/
int internalCounter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("System operational. Input control strings:");
}

void loop() {
  if (Serial.available() > 0) {
    String buffer = Serial.readStringUntil('\n');
    buffer.trim();

    if (buffer == "LED_ON") {
      digitalWrite(LED_BUILTIN, HIGH); [cite: 114]
      Serial.println("SUCCESS: Internal LED energized.");
    } 
    else if (buffer == "LED_OFF") {
      digitalWrite(LED_BUILTIN, LOW); [cite: 116]
      Serial.println("SUCCESS: Internal LED structural cut-off.");
    } 
    else if (buffer.startsWith("BLINK ")) {
      int dynamicLimit = buffer.substring(6).toInt();
      if (dynamicLimit >= 1 && dynamicLimit <= 9) { [cite: 118]
        for (int i = 0; i < dynamicLimit; i++) { [cite: 118]
          digitalWrite(LED_BUILTIN, HIGH); delay(250);
          digitalWrite(LED_BUILTIN, LOW);  delay(250);
          internalCounter++;
        }
        Serial.print("SUCCESS: Log processed. Absolute pulse operations count: ");
        Serial.println(internalCounter);
      } else {
        Serial.println("ERROR: Count parameter out of bounds (1-9).");
      }
    } 
    else if (buffer == "STATUS") {
      Serial.print("Target Pin LED_BUILTIN State: "); [cite: 120]
      Serial.println(digitalRead(LED_BUILTIN) ? "HIGH" : "LOW"); [cite: 120]
      Serial.print("Cumulative system run counter total: ");
      Serial.println(internalCounter);
    } 
    else if (buffer == "RESET") {
      internalCounter = 0; [cite: 122]
      Serial.println("SUCCESS: Running totals register cleared down to zero."); [cite: 122]
    } 
    else {
      Serial.println("ERROR: Unknown command"); [cite: 123]
    }
  }
}
