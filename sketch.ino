/*
 * SmartWeather IoT — Multi-Sensor Weather Monitoring
 * Intern: Beulah Jenifer P | URK23EC1047
 * CodSoft Embedded Systems Internship
 * Project: IoT Weather Station
 * Board: ESP32 | Simulation: Wokwi
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define DHT_PIN    4
#define DHT_TYPE   DHT22
#define LED_PIN    2
#define TEMP_ALERT 35.0
#define HUM_ALERT  80.0

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHT_TYPE);

float temperature, humidity, heatIndex;
int readingCount = 0;
float maxTemp = -999, minTemp = 999;
float maxHum  = -999, minHum  = 999;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  dht.begin();
  delay(2000);

  lcd.setCursor(0, 0);
  lcd.print("SmartWeather IoT");
  lcd.setCursor(0, 1);
  lcd.print(" Initializing...");
  delay(2000);
  lcd.clear();

  Serial.println("========================================");
  Serial.println("   SmartWeather IoT ESP32 Station");
  Serial.println("   Beulah Jenifer P | CodSoft 2025");
  Serial.println("========================================");
  Serial.println();
}

void publishMQTT(float temp, float hum, float hi) {
  StaticJsonDocument<256> doc;
  doc["device"]      = "ESP32-WeatherStation";
  doc["intern"]      = "Beulah Jenifer P";
  doc["id"]          = "URK23EC1047";
  doc["temperature"] = String(temp, 1);
  doc["humidity"]    = String(hum, 1);
  doc["heat_index"]  = String(hi, 1);
  doc["unit_temp"]   = "Celsius";
  doc["unit_hum"]    = "Percent";
  doc["alert"]       = (temp > TEMP_ALERT || hum > HUM_ALERT) ? "YES" : "NO";
  doc["reading_no"]  = readingCount;
  Serial.print("MQTT -> weather/station/data | ");
  serializeJson(doc, Serial);
  Serial.println();
}

void displayTemp() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(humidity, 1);
  lcd.print(" %");
}

void displayHeatIndex() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Heat Index:");
  lcd.setCursor(0, 1);
  lcd.print(heatIndex, 1);
  lcd.print("C ");
  if (heatIndex < 27)      lcd.print("Comfort");
  else if (heatIndex < 32) lcd.print("Caution");
  else if (heatIndex < 41) lcd.print("Danger!");
  else                     lcd.print("EXTREME!");
}

void displayStats() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MaxT:");
  lcd.print(maxTemp, 1);
  lcd.print(" H:");
  lcd.print(maxHum, 0);
  lcd.setCursor(0, 1);
  lcd.print("MinT:");
  lcd.print(minTemp, 1);
  lcd.print(" H:");
  lcd.print(minHum, 0);
}

void displayAlert() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("** HIGH ALERT **");
  lcd.setCursor(0, 1);
  if (temperature > TEMP_ALERT)
    lcd.print("High Temp!");
  else
    lcd.print("High Humidity!");
}

void loop() {
  delay(2000);

  humidity    = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT22 read failed! Retrying...");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    lcd.setCursor(0, 1);
    lcd.print("Retrying...");
    return;
  }

  heatIndex = dht.computeHeatIndex(temperature, humidity, false);
  readingCount++;

  if (temperature > maxTemp) maxTemp = temperature;
  if (temperature < minTemp) minTemp = temperature;
  if (humidity > maxHum)     maxHum  = humidity;
  if (humidity < minHum)     minHum  = humidity;

  Serial.println("----------------------------------------");
  Serial.print("Reading #"); Serial.println(readingCount);
  Serial.print("Temperature : "); Serial.print(temperature, 2); Serial.println(" C");
  Serial.print("Humidity    : "); Serial.print(humidity, 2);    Serial.println(" %");
  Serial.print("Heat Index  : "); Serial.print(heatIndex, 2);   Serial.println(" C");
  Serial.print("MaxT: "); Serial.print(maxTemp, 1);
  Serial.print("C  MinT: "); Serial.print(minTemp, 1); Serial.println("C");
  Serial.println("----------------------------------------");

  publishMQTT(temperature, humidity, heatIndex);

  bool alert = (temperature > TEMP_ALERT || humidity > HUM_ALERT);
  digitalWrite(LED_PIN, alert ? HIGH : LOW);

  int screen = readingCount % 3;
  if (alert)          displayAlert();
  else if (screen==0) displayTemp();
  else if (screen==1) displayHeatIndex();
  else                displayStats();
}
