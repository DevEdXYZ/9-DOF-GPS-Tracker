require('dotenv').config();
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const express = require('express');
const http = require('http');
const socketio = require('socket.io');
const path = require('path');

const serialPath = process.env.LORA_SERIAL_PORT || '/dev/ttyACM0';
const baudRate = parseInt(process.env.LORA_BAUD || '115200', 10);

const port = new SerialPort(serialPath, { baudRate });
const parser = port.pipe(new Readline({ delimiter: '\n' }));

const app = express();
const server = http.createServer(app);
const io = socketio(server);

app.use(express.static(path.join(__dirname, 'public')));
app.get('/config.js', (req, res) => {
  res.type('application/javascript');
  res.send(`window.GOOGLE_MAPS_API_KEY='${process.env.GOOGLE_MAPS_API_KEY || ''}';`);
});

parser.on('data', line => {
  io.emit('packet', line.trim());
});

const listenPort = process.env.PORT || 3000;
server.listen(listenPort, () => {
  console.log(`Server listening on http://localhost:${listenPort}`);
});
