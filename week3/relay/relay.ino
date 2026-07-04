#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int RELAY_PIN = 8; const int OVERRIDE = 7;
bool relayOn = false; bool manual = false;

void setup() {
  dht.begin(); pinMode(RELAY_PIN, OUTPUT); pinMode(OVERRIDE, INPUT_PULLUP);
}

void loop() {
  float temp = dht.readTemperature();
  if (digitalRead(OVERRIDE) == LOW) { manual = !manual; delay(300); }

  if (manual) {
    relayOn = true;
  } else {
    if (temp > 32.0)      relayOn = true; 
    else if (temp < 28.0) relayOn = false;
  }
  digitalWrite(RELAY_PIN, relayOn ? HIGH : LOW);
  delay(2000);
}
