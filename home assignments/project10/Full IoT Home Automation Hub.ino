#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqttServer = "broker.hivemq.com";
const char* mqttTopic = "iitjammu/yourname/home";

WiFiClient espClient;
PubSubClient mqttClient(espClient);
WebServer server(80);

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int MQ2_PIN = 35;
const int PIR_PIN = 13;
const int LDR_PIN = 34;

const int RELAY_FAN = 26;
const int RELAY_LIGHT = 27;

const int BUZZER = 14;

const int RED_LED = 25;
const int GREEN_LED = 2;

const int FAN_OVERRIDE_BTN = 0;
const int LIGHT_OVERRIDE_BTN = 32;

float g_temp = 0;
float g_hum = 0;

int g_gas = 0;
int g_light = 0;

bool g_pir = false;

bool fanOn = false;
bool lightOn = false;
bool gasAlert = false;

unsigned long lastSensorRead = 0;
unsigned long lastMqttPublish = 0;
unsigned long lastPirTime = 0;

unsigned long fanOverrideUntil = 0;
unsigned long lightOverrideUntil = 0;

unsigned long lastWiFiCheck = 0;

unsigned long startTime = 0;

int oledScreen = 0;
unsigned long lastScreenSwitch = 0;

void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  unsigned long start = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - start < 15000) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi Connection Failed");
  }
}

void connectMQTT() {
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  mqttClient.setServer(mqttServer, 1883);

  if (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");

    String clientID = "ESP32HomeHub-";
    clientID += String(random(0xffff), HEX);

    if (mqttClient.connect(clientID.c_str())) {
      Serial.println("MQTT Connected");
    } else {
      Serial.print("MQTT Failed, State: ");
      Serial.println(mqttClient.state());
    }
  }
}

void readSensors() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (!isnan(t)) {
    g_temp = t;
  }

  if (!isnan(h)) {
    g_hum = h;
  }

  int gasRaw = analogRead(MQ2_PIN);
  int lightRaw = analogRead(LDR_PIN);

  g_gas = map(gasRaw, 0, 4095, 0, 100);
  g_light = map(lightRaw, 0, 4095, 0, 100);

  g_gas = constrain(g_gas, 0, 100);
  g_light = constrain(g_light, 0, 100);

  if (digitalRead(PIR_PIN) == HIGH) {
    g_pir = true;
    lastPirTime = millis();
  } else if (millis() - lastPirTime > 180000UL) {
    g_pir = false;
  }

  Serial.println("----- Sensor Data -----");

  Serial.print("Temperature: ");
  Serial.print(g_temp);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(g_hum);
  Serial.println(" %");

  Serial.print("Gas: ");
  Serial.print(g_gas);
  Serial.println(" %");

  Serial.print("Light: ");
  Serial.print(g_light);
  Serial.println(" %");

  Serial.print("PIR: ");
  Serial.println(g_pir ? "YES" : "NO");
}

void applyAutomationRules() {
  if (millis() >= fanOverrideUntil) {
    if (!fanOn && g_temp > 32) {
      fanOn = true;
    }

    if (fanOn && g_temp < 28) {
      fanOn = false;
    }
  }

  if (millis() >= lightOverrideUntil) {
    if (!lightOn && g_light < 20 && g_pir) {
      lightOn = true;
    }

    if (lightOn && (g_light > 60 || !g_pir)) {
      lightOn = false;
    }
  }

  if (g_gas > 60) {
    gasAlert = true;
    fanOn = false;
    lightOn = false;
  } else {
    gasAlert = false;
  }

  digitalWrite(RELAY_FAN, fanOn ? LOW : HIGH);
  digitalWrite(RELAY_LIGHT, lightOn ? LOW : HIGH);

  digitalWrite(RED_LED, gasAlert ? HIGH : LOW);
  digitalWrite(GREEN_LED, gasAlert ? LOW : HIGH);

  digitalWrite(BUZZER, gasAlert ? HIGH : LOW);
}

void publishMQTT() {
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  if (!mqttClient.connected()) {
    connectMQTT();
  }

  if (!mqttClient.connected()) {
    return;
  }

  char jsonBuf[256];

  snprintf(
    jsonBuf,
    sizeof(jsonBuf),
    "{\"temp\":%.1f,\"humidity\":%.1f,\"gas\":%d,\"pir\":%d,\"light\":%d,\"fan\":%d,\"light_relay\":%d,\"alert\":%d}",
    g_temp,
    g_hum,
    g_gas,
    g_pir ? 1 : 0,
    g_light,
    fanOn ? 1 : 0,
    lightOn ? 1 : 0,
    gasAlert ? 1 : 0
  );

  mqttClient.publish(mqttTopic, jsonBuf);

  Serial.println("MQTT Data Published");
}

void uptimeString(char* buf, size_t bufSize) {
  unsigned long secs = (millis() - startTime) / 1000;

  int days = secs / 86400;
  int hours = (secs % 86400) / 3600;
  int mins = (secs % 3600) / 60;

  snprintf(
    buf,
    bufSize,
    "%dd:%dh:%dm",
    days,
    hours,
    mins
  );
}

void updateOLED() {
  char upBuf[24];

  if (millis() - lastScreenSwitch > 5000) {
    oledScreen = (oledScreen + 1) % 3;
    lastScreenSwitch = millis();
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);

  if (oledScreen == 0) {
    display.printf("Temp: %.1f C\n", g_temp);
    display.printf("Hum: %.1f %%\n", g_hum);

    if (WiFi.status() == WL_CONNECTED) {
      display.println("WiFi: Connected");
    } else {
      display.println("WiFi: Offline");
    }

  } else if (oledScreen == 1) {
    display.printf("Gas: %d %%\n", g_gas);
    display.printf("PIR: %s\n", g_pir ? "YES" : "NO");
    display.printf("LDR: %d %%\n", g_light);

  } else {
    uptimeString(upBuf, sizeof(upBuf));

    display.printf("Fan: %s\n", fanOn ? "ON" : "OFF");
    display.printf("Light: %s\n", lightOn ? "ON" : "OFF");
    display.printf("Alert: %s\n", gasAlert ? "YES" : "NO");
    display.printf("Up: %s\n", upBuf);
  }

  display.display();
}

void handleRoot() {
  char upBuf[24];

  uptimeString(upBuf, sizeof(upBuf));

  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<meta http-equiv='refresh' content='10'>";
  html += "<title>Home Automation Hub</title>";

  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#f2f2f2;padding:20px;}";
  html += ".card{background:white;padding:20px;margin:10px auto;max-width:500px;border-radius:15px;}";
  html += "a{display:inline-block;padding:12px 20px;margin:5px;background:#333;color:white;text-decoration:none;border-radius:8px;}";
  html += ".alert{color:red;font-weight:bold;}";
  html += "</style>";

  html += "</head>";
  html += "<body>";

  html += "<div class='card'>";
  html += "<h2>ESP32 Home Automation Hub</h2>";

  html += "<p>Temperature: ";
  html += String(g_temp, 1);
  html += " C</p>";

  html += "<p>Humidity: ";
  html += String(g_hum, 1);
  html += " %</p>";

  html += "<p>Gas: ";
  html += String(g_gas);
  html += " %</p>";

  html += "<p>PIR: ";
  html += g_pir ? "Motion Detected" : "No Motion";
  html += "</p>";

  html += "<p>Light: ";
  html += String(g_light);
  html += " %</p>";

  html += "<p>Fan: ";
  html += fanOn ? "ON" : "OFF";
  html += "</p>";

  html += "<p>Light Relay: ";
  html += lightOn ? "ON" : "OFF";
  html += "</p>";

  html += "<p>Gas Alert: ";
  html += gasAlert ? "<span class='alert'>ACTIVE</span>" : "Normal";
  html += "</p>";

  html += "<p>Uptime: ";
  html += upBuf;
  html += "</p>";

  html += "<a href='/toggleFan'>Toggle Fan</a>";
  html += "<a href='/toggleLight'>Toggle Light</a>";

  html += "</div>";

  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

void handleToggleFan() {
  fanOn = !fanOn;

  fanOverrideUntil = millis() + 600000UL;

  digitalWrite(RELAY_FAN, fanOn ? LOW : HIGH);

  server.sendHeader("Location", "/");
  server.send(303);
}

void handleToggleLight() {
  lightOn = !lightOn;

  lightOverrideUntil = millis() + 600000UL;

  digitalWrite(RELAY_LIGHT, lightOn ? LOW : HIGH);

  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(PIR_PIN, INPUT);

  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_LIGHT, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(FAN_OVERRIDE_BTN, INPUT_PULLUP);
  pinMode(LIGHT_OVERRIDE_BTN, INPUT_PULLUP);

  digitalWrite(RELAY_FAN, HIGH);
  digitalWrite(RELAY_LIGHT, HIGH);

  digitalWrite(BUZZER, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed!");
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Home Automation");
    display.println("Starting...");
    display.display();
  }

  connectWiFi();

  connectMQTT();

  server.on("/", HTTP_GET, handleRoot);

  server.on("/toggleFan", HTTP_GET, handleToggleFan);

  server.on("/toggleLight", HTTP_GET, handleToggleLight);

  server.begin();

  Serial.println("Web Server Started");

  startTime = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  server.handleClient();

  if (digitalRead(FAN_OVERRIDE_BTN) == LOW) {
    fanOn = !fanOn;

    fanOverrideUntil = currentMillis + 600000UL;

    digitalWrite(RELAY_FAN, fanOn ? LOW : HIGH);

    delay(300);
  }

  if (digitalRead(LIGHT_OVERRIDE_BTN) == LOW) {
    lightOn = !lightOn;

    lightOverrideUntil = currentMillis + 600000UL;

    digitalWrite(RELAY_LIGHT, lightOn ? LOW : HIGH);

    delay(300);
  }

  if (currentMillis - lastSensorRead >= 5000) {
    readSensors();

    applyAutomationRules();

    lastSensorRead = currentMillis;
  }

  if (currentMillis - lastMqttPublish >= 30000) {
    publishMQTT();

    lastMqttPublish = currentMillis;
  }

  if (currentMillis - lastWiFiCheck >= 30000) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi disconnected. Reconnecting...");
      connectWiFi();
    }

    lastWiFiCheck = currentMillis;
  }

  if (!mqttClient.connected()) {
    connectMQTT();
  }

  mqttClient.loop();

  updateOLED();
}
