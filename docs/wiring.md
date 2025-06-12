# Wiring Guide

This guide describes how to connect the components for both the wearable unit and the base station.

## Wearable Unit

| Feather RP2040 Pin | Component              | Pin      |
| ------------------ | --------------------- | -------- |
| 3V                 | GPS Breakout          | VIN      |
| GND                | GPS Breakout          | GND      |
| RX (GPIO1)         | GPS Breakout          | TX       |
| TX (GPIO0)         | GPS Breakout          | RX       |
| 3V                 | BNO085 IMU            | VIN      |
| GND                | BNO085 IMU            | GND      |
| SDA (GPIO2)        | BNO085 IMU            | SDA      |
| SCL (GPIO3)        | BNO085 IMU            | SCL      |
| LoRa Antenna       | RFM95 Module          | ANT      |

### Notes
- Use short wires to reduce noise.
- Keep the GPS antenna pointing upward for best reception.

## Base Station

Connect the second Feather RP2040 to your computer via USB. Attach the LoRa antenna to the board's RF connector. No additional wiring is required.
