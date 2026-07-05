const int btnCoin=2, btnSelect=3, btnCancel=4;
const int ledIdle=8, ledBusy=9, ledDispense=10;
enum State {IDLE, COIN_INSERTED, ITEM_SELECTED, DISPENSING};
State state = IDLE;
unsigned long stateTime = 0;
void changeState(State s);
void setLEDs() {
  digitalWrite(ledIdle, state == IDLE);
  digitalWrite(ledBusy, state == COIN_INSERTED || state == ITEM_SELECTED);
  digitalWrite(ledDispense, state == DISPENSING);
}

void changeState(State s) {
  state = s;
  stateTime = millis();
  setLEDs();
  const char* names[] = {"IDLE", "COIN_INSERTED", "ITEM_SELECTED", "DISPENSING"};
  Serial.print("Transition -> "); Serial.println(names[s]);
}

void setup() {
  pinMode(btnCoin, INPUT_PULLUP); pinMode(btnSelect, INPUT_PULLUP); pinMode(btnCancel, INPUT_PULLUP);
  pinMode(ledIdle, OUTPUT); pinMode(ledBusy, OUTPUT); pinMode(ledDispense, OUTPUT);
  Serial.begin(9600);
  changeState(IDLE);
}

void loop() {
  if (digitalRead(btnCancel) == LOW) { changeState(IDLE); delay(200); return; }

  switch (state) {
    case IDLE:
      if (digitalRead(btnCoin) == LOW) { changeState(COIN_INSERTED); delay(200); }
      break;
    case COIN_INSERTED:
      if (digitalRead(btnSelect) == LOW) { changeState(ITEM_SELECTED); delay(200); }
      break;
    case ITEM_SELECTED:
      if (millis() - stateTime > 1000) changeState(DISPENSING);
      break;
    case DISPENSING:
      if (millis() - stateTime > 2000) changeState(IDLE);
      break;
  }
}
