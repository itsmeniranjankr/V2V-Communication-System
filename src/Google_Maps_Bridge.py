import serial
import requests
import json

# Setup
PORT = 'COM3' # Change to your port
BAUD = 115200
FIREBASE_URL = "https://your-v2v-project.firebaseio.com/incidents.json"

try:
    ser = serial.Serial(PORT, BAUD, timeout=1)
    print("Bridge Active. Listening for V2V incidents...")
except:
    print("Error: Could not connect to Serial Port.")

incident_names = {
    "1": "Pothole Detected",
    "2": "Accident Reported",
    "3": "Disaster Zone",
    "4": "Road Blockage"
}

while True:
    line = ser.readline().decode('utf-8').strip()
    
    if "DATA_SYNC:" in line:
        data_part = line.split(":")[1]
        i_type, lat, lon, sev = data_part.split("|")
        
        payload = {
            "type": incident_names.get(i_type, "Unknown"),
            "latitude": float(lat),
            "longitude": float(lon),
            "severity": int(sev),
            "timestamp": {".sv": "timestamp"} # Server-side timestamp
        }
        
        # Push to Firebase (Google Maps will pull from here)
        response = requests.post(FIREBASE_URL, data=json.dumps(payload))
        
        if response.status_code == 200:
            print(f"Sync Success: {incident_names[i_type]} uploaded to Maps.")
        else:
            print("Sync Failed.")
