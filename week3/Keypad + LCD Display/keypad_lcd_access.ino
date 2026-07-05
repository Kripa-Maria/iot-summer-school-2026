#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'}, {'4','5','6','B'},
  {'7','8','9','C'}, {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(12, 11, 10, A5, A4, A3);
const int greenLed = A0, redLed = A1, buzzer = A2;
const String correctPIN = "1234";
String entered = "";
int wrongAttempts = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(greenLed, OUTPUT); pinMode(redLed, OUTPUT); pinMode(buzzer, OUTPUT);
  lcd.print("ENTER PIN:");
}

void loop() {
  if (wrongAttempts >= 3) {
    lcd.clear(); lcd.print("LOCKED 10s");
    tone(buzzer, 500, 500);
    delay(10000);
    wrongAttempts = 0;
    lcd.clear(); lcd.print("ENTER PIN:");
    entered = "";
    return;
  }

  char key = keypad.getKey();
  if (key) {
    if (key >= '0' && key <= '9') {
      entered += key;
      lcd.setCursor(entered.length() - 1, 1);
      lcd.print('*');
    }
    if (entered.length() == 4) {
      lcd.clear();
      if (entered == correctPIN) {
        lcd.print("ACCESS GRANTED");
        digitalWrite(greenLed, HIGH);
        delay(2000);
        digitalWrite(greenLed, LOW);
        wrongAttempts = 0;
      } else {
        lcd.print("ACCESS DENIED");
        digitalWrite(redLed, HIGH);
        tone(buzzer, 800, 300);
        delay(2000);
        digitalWrite(redLed, LOW);
        wrongAttempts++;
      }
      entered = "";
      lcd.clear();
      lcd.print("ENTER PIN:");
    }
  }
}
