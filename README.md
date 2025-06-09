# Real-Time Heart Rate Monitor

![MIT License](https://img.shields.io/badge/License-MIT-blue.svg)

This repository contains three Arduino sketches for building a real-time heart rate monitor using the MAX30102 IR sensor and a 128×64 OLED display. The system performs beat detection, BPM estimation, and waveform visualization without requiring a serial interface. Designed for both breadboard prototyping and custom PCB deployment using the Atmega328P microcontroller.

---

## Requirements

- Arduino IDE
- Libraries:
  - [SparkFun MAX3010x](https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library)
  - [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
  - [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)

---

## Hardware Setup

### Common Components

- MAX30102 IR heart rate sensor (I2C)
- SSD1306 128x64 OLED display (I2C)
- Atmega328P (Arduino-compatible)
- 16 MHz crystal + 22pF capacitors
- LED for heartbeat alert
- 10kΩ pull-up resistors (SDA/SCL, if needed)
- Power supply (e.g., 6V via coin cell or USB)

### Variants

- `heart-tracker-arduino`: For Arduino Uno/Nano boards
- `heart-tracker-breadboard`: Minimal Atmega328P setup on breadboard
- `heart-tracker-pcb`: Final version for custom PCB

### Schematic & PCB

- The `schematic/` folder contains:
  - Circuit schematic diagram
  - 3D rendering of the board

All hardware was designed using [EasyEDA](https://easyeda.com/).

---

## Programming

1. Choose the appropriate `.ino` file:
   - Use Arduino IDE
   - Select the correct board and programmer
2. For bare-metal Atmega328P (breadboard/PCB), use an ISP (e.g., Arduino as ISP)
3. Upload the sketch
4. The OLED will show:
   - Real-time IR signal waveform
   - Calculated BPM
   - Live IR readings
5. The LED flashes on each heartbeat (when IR signal is strong)

---

## License

MIT © 2025