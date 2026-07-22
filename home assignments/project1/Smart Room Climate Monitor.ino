#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHTPIN 4
#define DHTTYPE DHT22

#define RED_LED 25
#define GREEN_LED 26
#define BUZZER 27

DHT dht(DHTPIN, DHTTYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

unsigned long lastLog = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
  {
    Serial.println("OLED failed");
    while(1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0,0);
  display.println("Climate Monitor");
  display.display();

  delay(1000);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if(isnan(temp) || isnan(hum))
  {
    Serial.println("Sensor Error");
    return;
  }

  String status;

  if(temp > 40 || hum > 90)
  {
    status="DANGER";
    digitalWrite(RED_LED,HIGH);
    digitalWrite(GREEN_LED,LOW);
    digitalWrite(BUZZER,HIGH);
    delay(1000);
    digitalWrite(BUZZER,LOW);
  }
  else if(temp > 35 || hum > 80)
  {
    status="HOT";
    digitalWrite(RED_LED,HIGH);
    digitalWrite(GREEN_LED,LOW);
  }
  else if(temp > 25 && temp <35)
  {
    status="COMFORT";
    digitalWrite(RED_LED,LOW);
    digitalWrite(GREEN_LED,HIGH);
  }
  else
  {
    status="COOL";
    digitalWrite(RED_LED,LOW);
    digitalWrite(GREEN_LED,HIGH);
  }

  // OLED Display
  display.clearDisplay();

  display.setCursor(0,0);
  display.println("Climate Monitor");

  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.print("Hum : ");
  display.print(hum);
  display.println(" %");

  display.print("Status: ");
  display.println(status);

  display.display();

  // CSV Logging every 5 sec
  if(millis()-lastLog > 5000)
  {
    Serial.print(millis());
    Serial.print(",");
    Serial.print(temp);
    Serial.print(",");
    Serial.print(hum);
    Serial.print(",");
    Serial.println(status);

    lastLog=millis();
  }

  delay(2000);
}
