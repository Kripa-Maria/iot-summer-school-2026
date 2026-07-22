#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SOIL_PIN   34

#define RED_LED    25
#define GREEN_LED  26
#define BUZZER     27
#define RELAY      33

bool pumpOn = false;

unsigned long previousMillis = 0;
const long interval = 2000;      // Read every 2 seconds

void setup()
{
  Serial.begin(9600);
  delay(1000);

  Serial.println("ESP32 Smart Plant Watering Monitor");
  Serial.println("millis,soil(%),temperature(C),humidity(%),status,pump");

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  // Active LOW relay OFF
  digitalWrite(RELAY, HIGH);

  // Active LOW buzzer OFF
  digitalWrite(BUZZER, HIGH);

  dht.begin();

  Wire.begin(21,22);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
  {
    Serial.println("OLED Failed");
    while(1);
  }

  display.clearDisplay();
  display.display();
}

void loop()
{
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    int rawSoil = analogRead(SOIL_PIN);

    int moisture = map(rawSoil,3200,1200,0,100);
    moisture = constrain(moisture,0,100);

    float temp = dht.readTemperature();
    float hum  = dht.readHumidity();

    if(isnan(temp) || isnan(hum))
    {
      Serial.println("DHT Error");
      return;
    }

    String status;

    if(moisture < 30)
        status = "DRY";
    else if(moisture <= 70)
        status = "OPTIMAL";
    else
        status = "WET";

    if(!pumpOn && moisture < 30)
    {
        pumpOn = true;
        digitalWrite(RELAY, LOW);    
    }

    if(pumpOn && moisture > 40)
    {
        pumpOn = false;
        digitalWrite(RELAY, HIGH);    
    }

    if(status == "DRY")
    {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);

        digitalWrite(BUZZER, LOW);
        delay(500);
        digitalWrite(BUZZER, HIGH);
    }
    else
    {
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(BUZZER, HIGH);
    }

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0,0);
    display.print("Soil : ");
    display.print(moisture);
    display.println("%");

    display.setCursor(0,16);
    display.print("Temp : ");
    display.print(temp,1);
    display.println(" C");

    display.setCursor(0,32);
    display.print("Hum  : ");
    display.print(hum,1);
    display.println("%");

    display.setCursor(0,48);
    display.print(status);

    display.print(" ");

    if(pumpOn)
        display.print("PUMP ON");
    else
        display.print("PUMP OFF");

    display.display();

    Serial.print(millis());
    Serial.print(",");
    Serial.print(moisture);
    Serial.print(",");
    Serial.print(temp,1);
    Serial.print(",");
    Serial.print(hum,1);
    Serial.print(",");
    Serial.print(status);
    Serial.print(",");

    if(pumpOn)
        Serial.println("ON");
    else
        Serial.println("OFF");
  }
}
