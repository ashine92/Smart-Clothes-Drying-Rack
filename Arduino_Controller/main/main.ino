#include <SoftwareSerial.h>
#include <DHT.h>
#include "control.h"
#include "user_interface.h"
#include "remote.h"
#include "sensor.h"

#define menuButton 3
#define aButton 5
#define bButton 4

#define rainSensor A0
#define lightSensor A1
#define dhtPin 6
DHT dht(dhtPin, DHT11);

// Motor & limit switches
int motorA1 = 8;
int motorA2 = 9;
int switch1Pin = 11;
int switch2Pin = 10;

// UART for ESP32/Blynk
SoftwareSerial mySerial(12, 13); // TX=12, RX=13

// Mode enum
enum Mode { MODE_MENU, MODE_AUTO, MODE_MANUAL };
Mode currentMode = MODE_MENU;

// Sensor values
float temperature, humidity;
int rainValue, lightValue;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  // Pin setup
  pinMode(menuButton, INPUT_PULLUP);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(switch1Pin, INPUT_PULLUP);
  pinMode(switch2Pin, INPUT_PULLUP);

  dht.begin();
  stopMotor();

  initLCD();
  menu();
  mySerial.println("ARDUINO:READY");
}

void loop() {
  // Đọc cảm biến
  readSensors(temperature, humidity, rainValue, lightValue);

  // Gửi dữ liệu sang ESP32
  String data = "TEMP:" + String(temperature) + ",HUMI:" + String(humidity) +
                ",RAIN:" + String(rainValue) + ",LUX:" + String(lightValue);
  mySerial.println(data);

  // Nhận lệnh từ ESP32 (Blynk)
  if (mySerial.available() > 0) {
    String cmd = mySerial.readStringUntil('\n');
    Serial.print("Received from ESP32: ");
    Serial.println(cmd);
    handleRemoteCommand(cmd);

    // Nếu đang điều khiển từ xa, ưu tiên xử lý
    if (remoteControl) {
      if (remoteCmd == 1 && digitalRead(switch1Pin) == HIGH) {
        left();
      } else if (remoteCmd == 0 && digitalRead(switch2Pin) == HIGH) {
        right();
      } else {
        stopMotor();
      }
      return;
    }
  }

  // Chuyển chế độ bằng nút
  if (digitalRead(menuButton) == LOW) {
    currentMode = MODE_MENU;
    menu();
    delay(500);
  }

  // Xử lý theo chế độ
  switch (currentMode) {
    case MODE_MENU:
      if (digitalRead(aButton) == LOW) {
        currentMode = MODE_AUTO;
        delay(300);
      }
      else if (digitalRead(bButton) == LOW) {
        currentMode = MODE_MANUAL;
        delay(300);
      }
      break;

    case MODE_AUTO:
      automaticMode(temperature, humidity, rainValue < 500, lightValue);
      if (rainValue < 500) {
        if (digitalRead(switch1Pin) == HIGH) left();
        else stopMotor();
      } else {
        if (digitalRead(switch2Pin) == HIGH) right();
        else stopMotor();
      }
      break;

    case MODE_MANUAL:
      manualMode();
      if (digitalRead(bButton) == LOW && digitalRead(switch2Pin) == HIGH) right();
      else if (digitalRead(aButton) == LOW && digitalRead(switch1Pin) == HIGH) left();
      else stopMotor();
      break;
  }

  delay(2000); // Delay tránh đọc nút liên tục
}