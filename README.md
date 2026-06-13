# 🌤️ SmartWeather IoT — ESP32 Weather Monitoring Station

**Intern ID:** URK23EC1047
**Full Name:** Beulah Jenifer P
**No. of Weeks:** 4
**Project Name:** IoT Weather Station
**Project Scope:** Multi-sensor IoT weather monitoring system with real-time LCD display, MQTT JSON telemetry, heat index calculation, alert system and cloud integration simulation using ESP32 and DHT22


## 📌 Project Overview

SmartWeather IoT is a complete embedded IoT weather monitoring station built on ESP32. It reads real-time temperature and humidity from a DHT22 sensor, displays rotating data screens on a 16x2 LCD, publishes sensor data as MQTT JSON payloads simulating cloud telemetry, and triggers LED alerts when thresholds are exceeded. Fully simulated on Wokwi — no hardware required.


## 🧠 Features

- Real-time temperature and humidity sensing via DHT22
- Heat index calculation and comfort level classification
- Rotating LCD display — 3 screens every 2 seconds
- MQTT JSON payload publishing simulating ThingSpeak cloud
- LED alert system for high temperature or humidity
- Min/Max statistics tracking across all readings
- Serial monitor telemetry with formatted output


## 🛠️ Tech Stack

| Component | Detail |
|---|---|
| Microcontroller | ESP32 DevKit C V4 |
| Temperature Sensor | DHT22 |
| Display | LCD 1602 I2C (0x27) |
| Alert | Red LED + 1KΩ Resistor |
| Protocol | MQTT (simulated) |
| Data Format | JSON via ArduinoJson |
| Simulation | Wokwi |
| Language | C++ (Arduino Framework) |

---

## 📡 MQTT Payload Format

```json
{
  "device": "ESP32-WeatherStation",
  "intern": "Beulah Jenifer P",
  "id": "URK23EC1047",
  "temperature": "24.0",
  "humidity": "40.0",
  "heat_index": "23.5",
  "unit_temp": "Celsius",
  "unit_hum": "Percent",
  "alert": "NO",
  "reading_no": 12
}
```

---

## 🔌 Circuit Connections

| Component | ESP32 Pin |
|---|---|
| DHT22 VCC | 3V3 |
| DHT22 GND | GND |
| DHT22 DATA | GPIO 4 |
| LCD VCC | 3V3 |
| LCD GND | GND |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |
| LED Anode | GPIO 2 via 1KΩ |
| LED Cathode | GND |

---

## 📺 LCD Display Screens

**Screen 1 — Temperature and Humidity**

**Screen 2 — Heat Index**

**Screen 3 — Min/Max Statistics**

**Alert Screen — Triggered above threshold**

---

## 📊 Output Screenshots

### Temperature and Humidity Display
![Temp Humidity](outputs/screenshot1.png)

### Heat Index Display
![Heat Index](outputs/screenshot2.png)

### Serial Monitor MQTT Output
![Serial Monitor](outputs/screenshot3.png)

### Alert Screen
![Alert](outputs/screenshot4.png)

---

## 🚨 Alert Thresholds

| Parameter | Threshold |
|---|---|
| Temperature | > 35.0°C |
| Humidity | > 80.0% |

---


## 🎯 Key Results

| Metric | Value |
|---|---|
| Sensor | DHT22 — Temp + Humidity |
| Display | 16x2 LCD I2C — 3 rotating screens |
| Update Rate | Every 2 seconds |
| MQTT Topic | weather/station/data |
| Alert LED | GPIO 2 — triggers above threshold |
| Simulation | Wokwi — 100% online |

---

*Developed as part of CodSoft Embedded Systems Internship*
