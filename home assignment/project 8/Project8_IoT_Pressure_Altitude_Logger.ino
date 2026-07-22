#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP085.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_BMP085 bmp;

const int POT_PIN   = 34;
const int GREEN_LED = 25;
const int RED_LED   = 26;

float pressureLog[24];
int logIndex = 0, samplesTaken = 0;
unsigned long lastSample = 0, lastPageSwitch = 0;
bool showPage2 = false;
float localAltitude = 0;

const char* getTrend() {
  if (samplesTaken < 2) return "STABLE";
  float newest = pressureLog[(logIndex - 1 + 24) % 24];
  float oldest = pressureLog[logIndex % 24];
  float diffPa = (newest - oldest) * 100.0f;
  
  if (diffPa > 50)  return "RISING";
  if (diffPa < -50) return "FALLING";
  return "STABLE";
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!bmp.begin()) {
    Serial.println("BMP180 not found - check wiring");
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  float initialPressure = bmp.readPressure() / 100.0f;
  pressureLog[0] = initialPressure;
  logIndex = 1;
  samplesTaken = 1;
}

void loop() {
  int potRaw = analogRead(POT_PIN);
  localAltitude = map(potRaw, 0, 4095, 0, 2000);

  if (millis() - lastSample > 30000) {
    float pressure = bmp.readPressure() / 100.0f;
    float temp     = bmp.readTemperature();
    float altitude = bmp.readAltitude(101325);

    pressureLog[logIndex % 24] = pressure;
    logIndex++;
    samplesTaken++;

    float seaLevelP = pressure / pow(1 - (localAltitude / 44330.0), 5.255);
    const char* trend = getTrend();
    
    digitalWrite(GREEN_LED, strcmp(trend, "FALLING") != 0);
    digitalWrite(RED_LED,   strcmp(trend, "FALLING") == 0);

    Serial.printf("Pressure: %.1f hPa | Temp: %.1f C | Altitude: %.1f m | SeaLevelP: %.1f hPa | Trend: %s\n",
                  pressure, temp, altitude, seaLevelP, trend);

    lastSample = millis();
  }

  if (millis() - lastPageSwitch > 5000) {
    showPage2 = !showPage2;
    lastPageSwitch = millis();
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  if (!showPage2) {
    display.setTextSize(1);
    display.printf("Pressure: %.1f hPa\n\n", bmp.readPressure() / 100.0f);
    display.printf("Temp:     %.1f C\n\n", bmp.readTemperature());
    display.printf("Altitude: %.1f m\n", bmp.readAltitude(101325));
  } else {
    const char* trend = getTrend();
    display.setTextSize(2);
    display.println("Trend:\n");
    if (strcmp(trend, "RISING") == 0) display.println("  UP ^");
    else if (strcmp(trend, "FALLING") == 0) display.println("  DOWN v");
    else display.println("  STABLE");
  }

  display.display();
  delay(100);
}
