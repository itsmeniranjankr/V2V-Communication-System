#ifndef V2V_PROTOCOL_H
#define V2V_PROTOCOL_H

struct V2V_Packet {
    int vehicleID;      // Unique ID of the vehicle
    float latitude;     // GPS Lat
    float longitude;    // GPS Lon
    int incidentType;   // 1: Pothole, 2: Accident, 3: Disaster/Flood, 4: Road Block
    int severity;       // 1 (Minor) to 5 (Critical)
};

#endif
