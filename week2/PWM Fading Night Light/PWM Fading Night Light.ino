const int LED_PWM_PIN = 9;  
const int BUTTON_PIN = 2;   

int currentMode = 0;        
bool lastButtonState = HIGH;

void setup() {
  pinMode(LED_PWM_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  Serial.begin(9600);
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(50); 
    currentMode = (currentMode + 1) % 4;
    switch (currentMode) {
      case 0:
        analogWrite(LED_PWM_PIN, 0);   
        Serial.println("OFF (PWM: 0)");
        break;
      case 1:
        analogWrite(LED_PWM_PIN, 64);  
        Serial.println("Low (PWM: 64)");
        break;
      case 2:
        analogWrite(LED_PWM_PIN, 127); 
        Serial.println("Medium (PWM: 127)");
        break;
      case 3:
        analogWrite(LED_PWM_PIN, 255); 
        Serial.println("High (PWM: 255)");
        break;
    }
    while(digitalRead(BUTTON_PIN) == LOW);
  }
  lastButtonState = currentButtonState;
}
