#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4; const byte COLS = 4;
char keys[ROWS][COLS] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
byte rPins[ROWS] = {9, 8, 7, 6}; byte cPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rPins, cPins, ROWS, COLS);

const String pinSecret = "2026"; String entryBuffer = ""; int faults = 0;
const int GRN = 10; const int RED = 11; const int BUZZ = 12;

void setup() {
  lcd.init(); lcd.backlight();
  pinMode(GRN, OUTPUT); pinMode(RED, OUTPUT); pinMode(BUZZ, OUTPUT);
  refreshUI();
}
void refreshUI() { entryBuffer = ""; lcd.clear(); lcd.print("ENTER PIN:"); }

void loop() {
  char inputKey = keypad.getKey(); if (!inputKey) return;
  if (inputKey == '#') {
    if (entryBuffer == pinSecret) {
      lcd.clear(); lcd.print("ACCESS GRANTED");
      digitalWrite(GRN, HIGH); delay(3000); digitalWrite(GRN, LOW);
      faults = 0; refreshUI();
    } else {
      lcd.clear(); lcd.print("ACCESS DENIED");
      digitalWrite(RED, HIGH); tone(BUZZ, 800); delay(1500); noTone(BUZZ); digitalWrite(RED, LOW);
      faults++;
      if (faults >= 3) {
        lcd.clear(); lcd.print("SYSTEM LOCKED");
        digitalWrite(RED, HIGH); tone(BUZZ, 400); delay(10000); noTone(BUZZ); digitalWrite(RED, LOW);
        faults = 0;
      }
      refreshUI();
    }
  } else if (inputKey == '*') {
    refreshUI();
  } else {
    if (entryBuffer.length() < 4) {
      entryBuffer += inputKey; lcd.setCursor(entryBuffer.length() - 1, 1); lcd.print('*');
    }
  }
}
