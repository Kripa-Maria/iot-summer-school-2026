#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4; const byte COLS = 4;
char keys[ROWS][COLS] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
byte rPins[ROWS] = {9, 8, 7, 6}; byte cPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rPins, cPins, ROWS, COLS);
String secret = "2026"; String buffer = ""; int faults = 0;
const int GRN = 10; const int RED = 11; const int BUZZ = 12;
void setup() { lcd.init(); lcd.backlight(); pinMode(GRN, OUTPUT); pinMode(RED, OUTPUT); pinMode(BUZZ, OUTPUT); lcd.print("ENTER PIN:"); }
void loop() {
  char k = keypad.getKey(); if (!k) return;
  if (k == '#') {
    if (buffer == secret) { lcd.clear(); lcd.print("GRANTED"); digitalWrite(GRN, HIGH); delay(3000); digitalWrite(GRN, LOW); faults = 0; }
    else { lcd.clear(); lcd.print("DENIED"); digitalWrite(RED, HIGH); delay(1500); digitalWrite(RED, LOW); faults++;
      if (faults >= 3) { lcd.clear(); lcd.print("LOCKED"); delay(10000); faults = 0; }
    }
    buffer = ""; lcd.clear(); lcd.print("ENTER PIN:");
  } else if (k == '*') { buffer = ""; lcd.clear(); lcd.print("ENTER PIN:"); }
  else if (buffer.length() < 4) { buffer += k; lcd.setCursor(buffer.length()-1, 1); lcd.print('*'); }
}
