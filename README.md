# Smart Clothes Drying Rack

## 📌 Project Description
**Smart Clothes Drying Rack** is an IoT-based system that automatically controls the position of a clothes rack (extend/retract) based on weather conditions or user preferences. It uses Arduino and ESP32 microcontrollers to read sensor data, drive a motor, and communicate with the Blynk app for remote monitoring and control.

## ⚙️ Key Features
- **Automatic Mode:** The rack retracts when it rains or gets dark, and extends when the weather is sunny and dry.
- **Manual Mode:** Users can directly control the rack via physical buttons or the Blynk app.
- **Remote Control via Blynk:** Control the rack from anywhere using your smartphone.
- **Real-time Monitoring:** Displays temperature, humidity, rain status, and light levels.

## 🧰 Hardware Used
- **Microcontrollers:** Arduino UNO R3 + ESP32 (UART communication)
- **Sensors:**
  - DHT11 (Temperature and Humidity)
  - Rain sensor
  - LDR (Light sensor)
- **Motor:** DC motor to move the rack
- **Communication:**
  - UART between Arduino and ESP32
  - Wi-Fi via ESP32
- **Display & Interaction:**
  - LCD I2C screen (shows status and time)
  - 3 Push buttons (mode switch, automatic control, manual control)
- **Power Supply:** 12V/5V DC adapter

## 📂 File Structure
```
SmartClothesDryingRack/
│
├── Arduino/
│   ├── main.ino
│   ├── control.h
│   ├── control.ino
│   ├── remote.cpp
│   ├── remote.h
│   ├── sensor.cpp
│   ├── sensor.h
│   ├── user_interface.cpp
│   └── user_interface.cpp
│
├── ESP32/
│   ├── main.ino
│   ├── blynk_config.h
│   ├── blynk_config.cpp
│   ├── uart_comm.h
│   ├── uart_comm.cpp
│   ├── sensor_parser.h
│   └── sensor_parser.cpp
│
└── README.md
```
## 🔸Setup
1. Upload `Arduino_Controller/main.ino` to your Arduino.
2. Upload `ESP32_Connectivity/main.ino` to your ESP32.
3. Configure WiFi credentials in `blynk_config.cpp`.
4. Install Blynk app and set up virtual pins to control and monitor the device.

## 👩‍💻 Author
- **Email:** nguyenAtm0902@gmail.com
