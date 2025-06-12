#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#include "../config.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  LoRa.setPins(LORA_CS, LORA_RESET, LORA_IRQ);
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("LoRa init failed");
    while (1);
  }
  Serial.println("Base station ready");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      Serial.write(LoRa.read());
    }
    Serial.println();
  }
}
