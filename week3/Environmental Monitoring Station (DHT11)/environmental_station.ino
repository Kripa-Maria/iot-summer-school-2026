#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int RED_LED = 12; const int GRN_LED = 13;
void setup() {
  Serial.begin(9600); dht.begin();
  pinMode(RED_LED, OUTPUT); pinMode(GRN_LED, OUTPUT);
  Serial.println("timestamp,temp_C,temp_F,humidity");
}
void loop() {
  delay(2000);
  float c = dht.readTemperature(); float f = dht.readTemperature(true); float h = dht.readHumidity();
  if (isnan(h) || isnan(c) || isnan(f)) return;
  if (c > 35.0 || h > 80.0) { digitalWrite(RED_LED, HIGH); digitalWrite(GRN_LED, LOW); }
  else { digitalWrite(RED_LED, LOW); digitalWrite(GRN_LED, HIGH); }
  Serial.print(millis()); Serial.print(","); Serial.print(c, 1); Serial.print(",");
  Serial.print(f, 1); Serial.print(","); Serial.println(h, 0);
}
