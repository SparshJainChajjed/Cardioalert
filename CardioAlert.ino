// Prototype code for the CardioAlert project.
// Monitors heart rate and sends an SMS with GPS coordinates when
// readings fall outside of a user-defined range.
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial sim800(10, 11);
SoftwareSerial gpsSerial(8, 9);
TinyGPSPlus gps;

const int PULSE_PIN = A0;
int heartRate = 0;
const int NORMAL_MIN_BPM = 60;
const int NORMAL_MAX_BPM = 100;
const unsigned long ALERT_DELAY_MS = 60000;  // 1 minute between alerts
const unsigned long CHECK_INTERVAL_MS = 1000;
const unsigned long GPS_READ_MS = 2000;
const char PHONE_NUMBER[] = "+1234567890";
void setup() {
  Serial.begin(115200);
  sim800.begin(9600);
  gpsSerial.begin(9600);
  pinMode(PULSE_PIN, INPUT);
  sendCommand("AT", 1000);
  sendCommand("AT+CMGF=1", 1000);
  Serial.println("Setup complete.");
}

void loop() {
  heartRate = readPulseSensor();
  Serial.print("Heart Rate: ");
  Serial.println(heartRate);
  if (heartRate < NORMAL_MIN_BPM || heartRate > NORMAL_MAX_BPM) {
    Serial.println("Abnormal heart rate detected! Sending alert...");
    String gpsCoordinates = getGPSCoordinates();
    sendSMS(gpsCoordinates);
    delay(ALERT_DELAY_MS);
  }
  delay(CHECK_INTERVAL_MS);
}

int readPulseSensor() {
  int sensorValue = analogRead(PULSE_PIN);
  int bpm = map(sensorValue, 0, 1023, 50, 150);
  return bpm;
}

String getGPSCoordinates() {
  unsigned long startTime = millis();
  while (millis() - startTime < GPS_READ_MS) {
    while (gpsSerial.available()) {
      char c = gpsSerial.read();
      gps.encode(c);
    }
  }
  if (gps.location.isValid()) {
    String gpsData = String(gps.location.lat(), 6) + ", " + String(gps.location.lng(), 6);
    Serial.print("GPS Data: ");
    Serial.println(gpsData);
    return gpsData;
  } else {
    Serial.println("Unable to get GPS coordinates.");
    return "Unable to get GPS coordinates.";
  }
}

void sendSMS(String gpsCoordinates) {
  sim800.println("AT+CMGS=\"" + PHONE_NUMBER + "\"");
  delay(1000);
  sim800.print("ALERT! Abnormal heart rate detected.\n");
  sim800.print("Heart Rate: ");
  sim800.print(heartRate);
  sim800.print(" BPM\n");
  sim800.print("Location: ");
  sim800.print(gpsCoordinates);
  sim800.write(26);
  delay(5000);
  Serial.println("SMS Sent!");
}

void sendCommand(const char* cmd, unsigned long timeout) {
  sim800.println(cmd);
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (sim800.available()) {
      String response = sim800.readString();
      Serial.print("Response: ");
      Serial.println(response);
      break; 
    }
  }
}
