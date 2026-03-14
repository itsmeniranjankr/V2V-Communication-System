#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "V2V_Protocol.h"

RF24 radio(7, 8);
const byte address[6] = "V2V_01";

void setup() {
    Serial.begin(115200);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.startListening();
}

void loop() {
    if (radio.available()) {
        V2V_Packet p;
        radio.read(&p, sizeof(p));

        // Format for Python: "TYPE|LAT|LON|SEVERITY"
        Serial.print("DATA_SYNC:");
        Serial.print(p.incidentType); Serial.print("|");
        Serial.print(p.latitude, 6); Serial.print("|");
        Serial.print(p.longitude, 6); Serial.print("|");
        Serial.println(p.severity);

        // Simple Dashboard Alert Logic
        if (p.incidentType == 1) Serial.println(">>> DISPLAY: CAUTION! POTHOLE AHEAD.");
        if (p.incidentType == 2) Serial.println(">>> DISPLAY: CRITICAL! ACCIDENT REPORTED.");
        if (p.incidentType == 3) Serial.println(">>> DISPLAY: EMERGENCY! DISASTER AREA.");
        if (p.incidentType == 4) Serial.println(">>> DISPLAY: ALERT: ROAD BLOCK AHEAD.");
    }
}
