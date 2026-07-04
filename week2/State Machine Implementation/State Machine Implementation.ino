/******************************************************************************
 * Author: Kripa Maria [cite: 55, 248]
 * Date: July 2026 [cite: 55, 248]
 * Description: Vending finite state machine pattern framework tracking[cite: 131].
 * * STATE TRANSITION GRAPH DESCRIPTION DIAGRAM [cite: 133]
 * [ IDLE ] ───(Insert Coin Button)───> [ COIN_INSERTED ]
 * ▲               │                       │
 * │         (Cancel Button)               │(Select Item Button)
 * │               ▼                       ▼
 * └───────────────┴─────────────── [ ITEM_SELECTED ] ──> [ DISPENSING ] ──> (Auto)
 *****************************************************************************/
enum AutomationState { IDLE, COIN_INSERTED, ITEM_SELECTED, DISPENSING }; [cite: 131]
AutomationState dynamicMachineState = IDLE;

const int BTN_COIN = 2; const int BTN_SELECT = 3; const int BTN_CANCEL = 4;
const int LED_IDLE = 10; const int LED_COIN = 11; const int LED_SELECT = 12;

void setup() {
  pinMode(BTN_COIN, INPUT_PULLUP); pinMode(BTN_SELECT, INPUT_PULLUP); pinMode(BTN_CANCEL, INPUT_PULLUP);
  pinMode(LED_IDLE, OUTPUT); pinMode(LED_COIN, OUTPUT); pinMode(LED_SELECT, OUTPUT);
  Serial.begin(9600);
  Serial.println("STATE UPDATE: Current baseline register mode initialized to IDLE."); [cite: 133]
}

void transitionTo(AutomationState nextTargetState, String logTextDescription) {
  dynamicMachineState = nextTargetState;
  Serial.print("STATE TRANSITION EVENT: "); Serial.println(logTextDescription); [cite: 133]
}

void loop() {
  // Drive hardware system LED indicator arrays matching active configuration states [cite: 132]
  digitalWrite(LED_IDLE,   dynamicMachineState == IDLE ? HIGH : LOW);
  digitalWrite(LED_COIN,   dynamicMachineState == COIN_INSERTED ? HIGH : LOW);
  digitalWrite(LED_SELECT, dynamicMachineState == ITEM_SELECTED ? HIGH : LOW);

  switch (dynamicMachineState) {
    case IDLE:
      if (digitalRead(BTN_COIN) == LOW) { delay(200); transitionTo(COIN_INSERTED, "IDLE -> COIN_INSERTED"); } [cite: 132]
      break;
      
    case COIN_INSERTED:
      if (digitalRead(BTN_SELECT) == LOW) { delay(200); transitionTo(ITEM_SELECTED, "COIN_INSERTED -> ITEM_SELECTED"); } [cite: 132]
      if (digitalRead(BTN_CANCEL) == LOW) { delay(200); transitionTo(IDLE, "COIN_INSERTED -> IDLE (Purchase Aborted)"); } [cite: 132]
      break;
      
    case ITEM_SELECTED:
      transitionTo(DISPENSING, "ITEM_SELECTED -> DISPENSING (Dispensing product load active)");
      break;
      
    case DISPENSING:
      delay(2000); // Wait out completion cycle task delay routines
      transitionTo(IDLE, "DISPENSING -> IDLE (Delivery successful. Vault unlocked)");
      break;
  }
}
