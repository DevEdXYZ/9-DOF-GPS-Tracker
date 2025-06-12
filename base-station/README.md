# Base Station Server

Node.js server that receives LoRa packets from the Feather RP2040 via serial port and displays data on a live map using Google Maps.

## Setup

1. Install Node.js (v18+ recommended).
2. Copy `.env.example` to `.env` and update `LORA_SERIAL_PORT`, `LORA_BAUD` and `GOOGLE_MAPS_API_KEY`.
3. Install dependencies:
   ```bash
   npm install
   ```
4. Run the server:
   ```bash
   npm start
   ```
5. Open `http://localhost:3000` in your browser.

The map will automatically update when packets are received via LoRa.
