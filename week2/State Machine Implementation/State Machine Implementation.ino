enum MachineState { STATE_IDLE, STATE_COIN_INSERTED, STATE_DISPENSING };
MachineState currentState = STATE_IDLE;

const int PIN_COIN = 2;
const int PIN_SELECT = 3;
const int PIN_CANCEL = 4;
const int PIN_ACTUATOR = 13;

void setup() {
  pinMode(PIN_COIN, INPUT_PULLUP);
  pinMode(PIN_SELECT, INPUT_PULLUP);
  pinMode(PIN_CANCEL, INPUT_PULLUP);
  pinMode(PIN_ACTUATOR, OUTPUT);
  digitalWrite(PIN_ACTUATOR, LOW);
  Serial.begin(9600);
}

void loop() {
  switch (currentState) {
    case STATE_IDLE:
      if (digitalRead(PIN_COIN) == LOW) {
        delay(50);
        currentState = STATE_COIN_INSERTED;
        Serial.println("Coin Detected!");
        while(digitalRead(PIN_COIN) == LOW);
      }
      break;

    case STATE_COIN_INSERTED:
      if (digitalRead(PIN_SELECT) == LOW) {
        delay(50);
        currentState = STATE_DISPENSING;
        Serial.println("Item Selected!");
        while(digitalRead(PIN_SELECT) == LOW);
      } 
      else if (digitalRead(PIN_CANCEL) == LOW) {
        delay(50);
        currentState = STATE_IDLE;
        Serial.println("Cancelled. Refunding coin.");
        while(digitalRead(PIN_CANCEL) == LOW);
      }
      break;

    case STATE_DISPENSING:
      digitalWrite(PIN_ACTUATOR, HIGH);
      delay(2000);
      digitalWrite(PIN_ACTUATOR, LOW);
      currentState = STATE_IDLE;
      Serial.println("Dispense Complete. Status: IDLE.");
      break;
  }
}
