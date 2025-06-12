#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GPS.h>
#include <Adafruit_BNO08x.h>
#include <LoRa.h>

#include "../config.h"

Adafruit_GPS GPS(&Serial1);
Adafruit_BNO08x  bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("Wearable tracker startup");

  GPS.begin(GPS_BAUD);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);

  if (!bno08x.begin_I2C()) {
    Serial.println("BNO08x not detected");
    while (1);
  }
  bno08x.enableReport(SH2_ROTATION_VECTOR);

  LoRa.setPins(LORA_CS, LORA_RESET, LORA_IRQ);
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("LoRa init failed");
    while (1);
  }
  Serial.println("Setup complete");
}

void loop() {
  GPS.read();
  if (GPS.newNMEAreceived()) {
    GPS.parse(GPS.lastNMEA());
  }

  if (bno08x.getSensorEvent(&sensorValue)) {
    float yaw   = sensorValue.un.rotationVector.real * 360.0f;
    float pitch = sensorValue.un.rotationVector.i * 360.0f;
    float roll  = sensorValue.un.rotationVector.j * 360.0f;

    LoRa.beginPacket();
    LoRa.print(GPS.latitude, 6); LoRa.print(',');
    LoRa.print(GPS.longitude, 6); LoRa.print(',');
    LoRa.print(GPS.altitude); LoRa.print(',');
    LoRa.print(yaw, 2); LoRa.print(',');
    LoRa.print(pitch, 2); LoRa.print(',');
    LoRa.print(roll, 2);
    LoRa.endPacket();
  }
  delay(1000);
}
