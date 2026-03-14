# V2V-Sync: Decentralized Vehicle-to-Vehicle Communication & Live Hazard Mapping

## 📌 Project Overview
V2V-Sync is a standalone communication system that allows vehicles to exchange real-time safety data without relying on cellular infrastructure. By utilizing RF mesh networking, vehicles can alert each other about potholes, accidents, and road blocks, while simultaneously updating a global Google Maps layer for the wider community.

## 🚀 Key Features
- **Standalone Mesh Networking:** Operates in cellular dead zones using NRF24L01.
- **Pothole Detection:** Real-time Z-axis monitoring via MPU6050 Accelerometer.
- **Live Google Maps Integration:** Automated hazard marking on a centralized map.
- **Disaster Resilience:** "Daisy-chain" message relaying for blocked road alerts.

## 🛠️ Hardware Stack
- **Microcontroller:** ESP32 (for WiFi/Cloud) or Arduino Uno.
- **Communication:** NRF24L01+ PA/LNA (Long Range RF).
- **Sensors:** MPU6050 (IMU), NEO-6M (GPS Module).
- **Display:** 16x2 I2C LCD for driver alerts.

## 📂 File Structure
- `/src`: Arduino (.ino) and Python (.py) source code.
- `/schematics`: Circuit diagrams and wiring.
- `/docs`: Project report and V2X roadmap.
