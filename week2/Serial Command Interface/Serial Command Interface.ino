const int ledPin = 13;
bool ledState = false;
int blinkCounter = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready. Commands: LED_ON, LED_OFF, BLINK_X, STATUS, RESET");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "LED_ON") { digitalWrite(ledPin, HIGH); ledState = true; Serial.println("LED ON"); }
    else if (cmd == "LED_OFF") { digitalWrite(ledPin, LOW); ledState = false; Serial.println("LED OFF"); }
    else if (cmd.startsWith("BLINK_")) {
      int x = cmd.substring(6).toInt();
      if (x >= 1 && x <= 9) {
        for (int i = 0; i < x; i++) {
          digitalWrite(ledPin, HIGH); delay(200);
          digitalWrite(ledPin, LOW); delay(200);
          blinkCounter++;
        }
        Serial.println("Blinked " + String(x) + " times");
      } else Serial.println("ERROR: Unknown command");
    }
    else if (cmd == "STATUS") { Serial.println(ledState ? "PIN 13: HIGH" : "PIN 13: LOW"); }
    else if (cmd == "RESET") { blinkCounter = 0; Serial.println("Blink counter reset"); }
    else Serial.println("ERROR: Unknown command");
  }
}
