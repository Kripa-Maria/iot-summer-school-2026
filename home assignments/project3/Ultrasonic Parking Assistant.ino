#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Ultrasonic Sensor
#define TRIG_PIN 9
#define ECHO_PIN 10

// LEDs
#define GREEN_LED 2
#define YELLOW_LED 3
#define RED_LED 4

// Buzzer
#define BUZZER 6

unsigned long previousBeep = 0;
unsigned long previousSerial = 0;

float distance = 0;
String zone = "SAFE";

float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float dist = duration * 0.034 / 2;

  return dist;
}

float averageDistance() {
  float total = 0;
  for (int i = 0; i < 5; i++) {
    total += measureDistance();
  }
  return total / 5.0;
}

void updateOLED(float dist) {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);
  display.print(dist,0);
  display.print(" cm");

  display.setTextSize(1);
  display.setCursor(0,25);
  display.print("Zone: ");
  display.print(zone);

  int bar = map(constrain((int)dist,0,100),100,0,0,120);

  display.drawRect(4,50,120,10,SSD1306_WHITE);
  display.fillRect(4,50,bar,10,SSD1306_WHITE);

  display.display();
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);

  pinMode(GREEN_LED,OUTPUT);
  pinMode(YELLOW_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);

  pinMode(BUZZER,OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    while(true);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  distance = averageDistance();

  digitalWrite(GREEN_LED,LOW);
  digitalWrite(YELLOW_LED,LOW);
  digitalWrite(RED_LED,LOW);

  unsigned long currentMillis = millis();

  noTone(BUZZER);

  if(distance > 60){
      zone="SAFE";
      digitalWrite(GREEN_LED,HIGH);
  }
  else if(distance >30){
      zone="CAUTION";
      digitalWrite(YELLOW_LED,HIGH);

      if(currentMillis-previousBeep>=800){
          tone(BUZZER,1000,100);
          previousBeep=currentMillis;
      }
  }
  else if(distance >15){
      zone="CLOSE";
      digitalWrite(YELLOW_LED,HIGH);
      digitalWrite(RED_LED,HIGH);

      if(currentMillis-previousBeep>=300){
          tone(BUZZER,1000,100);
          previousBeep=currentMillis;
      }
  }
  else{
      zone="DANGER";
      digitalWrite(RED_LED,HIGH);
      tone(BUZZER,1200);
  }

  updateOLED(distance);

  if(currentMillis-previousSerial>=500){
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print(" cm");

      Serial.print(" | Zone: ");
      Serial.println(zone);

      previousSerial=currentMillis;
  }
}
