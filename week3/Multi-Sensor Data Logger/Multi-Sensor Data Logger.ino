#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int TRIG_PIN = 6; const int ECHO_PIN = 7; const int LDR_PIN = A1;
void setup() { Serial.begin(9600); dht.begin(); pinMode(TRIG_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT); }
void loop() {
  delay(5000);
  float t = dht.readTemperature(); float h = dht.readHumidity();
  int light = map(analogRead(LDR_PIN), 0, 1023, 0, 100);
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2); digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10); digitalWrite(TRIG_PIN, LOW);
  long dist = (pulseIn(ECHO_PIN, HIGH) * 0.034) / 2;
  Serial.println("=== SENSOR LOG");
  Serial.print("Time : "); Serial.print(millis()); Serial.println(" ms");
  Serial.print("Temp : "); Serial.print(t, 1); Serial.print(" C Humidity: "); Serial.print(h, 0); Serial.println("%");
  Serial.print("Light : "); Serial.print(light); Serial.println("% (Bright)");
  Serial.print("Distance : "); Serial.print(dist); Serial.println(" cm");
}
