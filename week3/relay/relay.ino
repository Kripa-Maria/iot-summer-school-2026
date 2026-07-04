#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int RELAY_PIN = 8;
const int OVERRIDE  = 7;
bool relayOn = false;
bool manual  = false;

void setup() {
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(OVERRIDE, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  float temp = dht.readTemperature();
  if (digitalRead(OVERRIDE) == LOW) { manual = !manual; delay(300); }

  if (manual) {
    relayOn = true;
    Serial.println("ALERT: Manual control override triggered.");
  } else {
    // Environmental climate hysteresis window scaling bands
    if (temp > 32.0)      relayOn = true; 
    else if (temp < 28.0) relayOn = false;
  }

  digitalWrite(RELAY_PIN, relayOn ? HIGH : LOW);
  Serial.print("Temp: "); Serial.print(temp, 1);
  Serial.print(" C | Relay Power Load State: "); Serial.println(relayOn ? "ON" : "OFF");
  delay(2000);
}
