#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "V2V_Protocol.h"

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "V2V_01";
Adafruit_MPU6050 mpu;

void setup() {
    Serial.begin(115200);
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MAX); // Max range
    mpu.begin();
}

void loop() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    V2V_Packet incident = { 101, 10.3254, 76.3312, 0, 0 };

    // 1. POTHOLE DETECTION (Z-Axis Jolt)
    if (a.acceleration.z > 16.0 || a.acceleration.z < 4.0) {
        incident.incidentType = 1;
        incident.severity = 2;
        broadcastIncident(incident);
    }

    // 2. ACCIDENT DETECTION (High Impact / Sudden Stop)
    if (abs(a.acceleration.x) > 25.0 || abs(a.acceleration.y) > 25.0) {
        incident.incidentType = 2;
        incident.severity = 5;
        broadcastIncident(incident);
    }

    // 3. MANUAL / DISASTER / BLOCK (Simulated via Serial or Button)
    if (Serial.available() > 0) {
        char type = Serial.read();
        if (type == 'D') { // Disaster
            incident.incidentType = 3;
            incident.severity = 5;
            broadcastIncident(incident);
        } else if (type == 'B') { // Road Block
            incident.incidentType = 4;
            incident.severity = 3;
            broadcastIncident(incident);
        }
    }
    delay(100);
}

void broadcastIncident(V2V_Packet p) {
    radio.write(&p, sizeof(p));
    Serial.print("Broadcasted Incident Type: ");
    Serial.println(p.incidentType);
}
