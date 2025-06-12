# 9-DOF GPS Tracker

A wearable GPS + 9-DOF IMU tracker that logs fused position data (GPS + sensor fusion) and streams it over LoRa to a base station. The base station relays incoming data to a web UI with a 3D map overlay (e.g., Google Maps) to visualize route history and current position.

---

## Table of Contents

- [Features](#features)  
- [Hardware](#hardware)  
  - [Wearable Unit](#wearable-unit)  
  - [Base Station](#base-station)  
  - [Power & Enclosure](#power--enclosure)  
  - [Parts List & Suppliers](#parts-list--suppliers)  
- [Software](#software)  
  - [Firmware (RP2040)](#firmware-rp2040)  
  - [Base Station Server/UI](#base-station-serverui)  
- [Assembly](#assembly)  
  - [Wiring](#wiring)  
  - [3D-Printed Enclosure](#3d-printed-enclosure)  
- [Usage](#usage)  
- [Troubleshooting](#troubleshooting)  
- [Contributing](#contributing)  
- [License](#license)  

---

## Features

- **GPS Positioning**  
  - Adafruit Ultimate GPS (66-channel, 10 Hz) for real-world XYZ coordinates.
- **9-DOF Sensor Fusion**  
  - BNO085 IMU for absolute orientation and displacement.
- **LoRa Communications**  
  - RP2040 Feather + RFM95 (915 MHz) for long-range, low-power data link.
- **Rugged Enclosures**  
  - Custom 3D-printed cases for both wearable and base units.
- **Live Mapping UI**  
  - Web server overlays incoming point-cloud and current position on a 3D map.

---

## Hardware

### Wearable Unit

- **Microcontroller & Radio:**  
  - Adafruit Feather RP2040 with RFM95 LoRa Radio (915 MHz)  
- **GPS Module:**  
  - Adafruit Ultimate GPS Breakout (66-channel, 10 Hz, Version 3)  
- **IMU:**  
  - Adafruit 9-DOF Orientation IMU Fusion Breakout (BNO085/BNO080)  
- **Antenna:**  
  - 915 MHz LoRa whip antenna  
- **Battery:**  
  - 3.7 V, 2000 mAh LiPo battery (JST connector)  

### Base Station

- **Microcontroller & Radio:**  
  - Adafruit Feather RP2040 with RFM95 LoRa Radio (915 MHz)  
- **Connection:**  
  - USB to PC/Laptop  
- **Server/UI:**  
  - Local web server (Node.js/Python)  
  - Web UI with map overlay (e.g., Google Maps JavaScript API)  

### Power & Enclosure

- **Battery Charger (optional):**  
  - MCP73831-based LiPo charger or Adafruit LiPo charging board  
- **Enclosures:**  
  - Designed in CAD (Fusion 360/FreeCAD)  
  - Printed in PLA/ABS for durability  
  - Rubber gaskets or O-rings for weather resistance  

### Parts List & Suppliers

| Component                                                    | Qty | Supplier                                         | Notes                  |
| ------------------------------------------------------------ | :-: | ------------------------------------------------ | ---------------------- |
| Adafruit Ultimate GPS Breakout (66 ch, 10 Hz, Version 3)     |  1  | RS / Mouser / DigiKey / Pi Hut / Amazon UK       | ~£25–£52               |
| Adafruit 9-DOF IMU Fusion Breakout (BNO085/BNO080, STEMMA)   |  1  | Mouser / Amazon UK                               | ~£20–£34               |
| Adafruit Feather RP2040 + RFM95 LoRa Radio (915 MHz, STEMMA) |  2  | Pi Hut / Mouser / DigiKey / Amazon UK            | ~£24–£38 each          |
| 3.7 V, 2000 mAh LiPo Battery Pack (JST connector)            |  1  | Amazon UK                                        | ~£25                   |
| LoRa Whip Antennas (915 MHz)                                  |  2  | Amazon UK / eBay                                 | ~£5 each               |
| LiPo Charging Module (e.g., Adafruit Micro Lipo)             |  1  | Adafruit / Pi Hut                                | ~£8                    |

---

## Software

### Firmware (RP2040)

1. **Clone repo**  
   ```bash
   git clone https://github.com/your-username/9-DOF-GPS-Tracker.git
   cd 9-DOF-GPS-Tracker/firmware
   ```
2. **Install dependencies**  
   - Arduino Core for RP2040  
   - LoRa library (RadioHead or LoRa by Sandeep Mistry)  
   - Adafruit GPS and BNO08x libraries  
3. **Configure**  
   - Edit `config.h` for LoRa frequency, GPS UART pins, and I²C pins.  
4. **Build & Flash**  
   ```bash
   arduino-cli compile --fqbn adafruit:rp2040:adafruit_feather_rp2040
   arduino-cli upload -p /dev/ttyUSB0 --fqbn adafruit:rp2040:adafruit_feather_rp2040
   ```

### Base Station Server/UI

1. **Clone & install**
   ```bash
   cd base-station
   npm install
   ```
2. **Configure**  
   - In `.env`, set `LORA_SERIAL_PORT`, `LORA_BAUD`, and `GOOGLE_MAPS_API_KEY`.  
3. **Run**  
   ```bash
   npm start
   ```
4. **Open**  
   - Browser → `http://localhost:3000`  
   - See live point-cloud and current position on map.

---

## Assembly

### Wiring

```
Wearable Unit:
  Feather RP2040 I²C SDA → BNO085 SDA
                    SCL → BNO085 SCL
  Feather UART TX → GPS RX
         UART RX → GPS TX
  Feather 3V → GPS 3V, BNO085 3V
  Feather GND → GPS GND, BNO085 GND

Base Station:
  Feather USB → PC/Laptop
  Feather 3V/GND → (power only)
```

For detailed pin references and assembly photos, see [docs/wiring.md](docs/wiring.md).

### 3D-Printed Enclosure

- **Files:** `cases/wearable.stl`, `cases/base_station.stl`  
- **Material:** PLA or ABS  
- **Settings:**  
  - Layer height: 0.2 mm  
  - Infill: 30%  
  - Supports: minimal  
- **Assembly:**  
  1. Mount Feather to PCB standoffs.  
  2. Slide in sensor modules.  
  3. Secure lid with M2 screws & O-ring gasket.  
  4. Route antenna through sealed gland.

---

## Usage

1. Charge the wearable unit.  
2. Power on wearable and base station.  
3. Launch the web UI; verify LoRa link.  
4. Wear the device; start moving.  
5. Watch real-time route and orientation on map.

---

## Troubleshooting

- **No GPS Fix:**  
  - Move outdoors with clear sky view.  
  - Check GPS antenna orientation.  
- **LoRa Link Fails:**  
  - Verify matching frequency (915 MHz).  
  - Check antenna connections.  
- **IMU Drift / No Data:**  
  - Ensure correct I²C wiring.  
  - Call `imu.begin()` before reading.

---

## Contributing

1. Fork the repo  
2. Create branch (`git checkout -b feature/my-feature`)  
3. Commit (`git commit -m "Add feature"`)  
4. Push (`git push origin feature/my-feature`)  
5. Open a Pull Request  

---

## License

This project is licensed under the [MIT License](LICENSE).
