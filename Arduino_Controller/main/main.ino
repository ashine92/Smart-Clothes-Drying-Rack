#include "control.h"
#include "user_interface.h"  // Include the user_interface header for the function declarations
#include <TimeLib.h>         // Include TimeLib to handle time functions

#define menuButton 3
#define aButton 5
#define bButton 4

#define rainSensor A0
#define lightSensor A1
#define dhtPin 6

#include <DHT.h>
DHT dht(dhtPin, DHT11);

int motorA1 = 8;
int motorA2 = 9;
int switch1Pin = 11;
int switch2Pin = 10;

enum Mode { MODE_MENU, MODE_AUTO, MODE_MANUAL, MODE_TIMER };
Mode currentMode = MODE_MENU;

float temperature = 0;
float humidity = 0;
int rainValue = 0;
int lightValue = 0;

int pushInHour = 6;     // Giờ đẩy sào
int pushInMinute = 30;  // Phút đẩy sào
int pullOutHour = 7;    // Giờ thu sào
int pullOutMinute = 0;  // Phút thu sào

void setup() {
  Serial.begin(9600);

  pinMode(menuButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(switch1Pin, INPUT_PULLUP);
  pinMode(switch2Pin, INPUT_PULLUP);
  
  dht.begin();
  lcd.backlight();
  stopMotor();
  initLCD();
  menu();
}

void loop() {
  // Đọc giá trị từ các cảm biến
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Lỗi đọc cảm biến DHT11!");
    return;
  }

  temperature = t;
  humidity = h;
  rainValue = analogRead(rainSensor);
  lightValue = analogRead(lightSensor);

  // Debug Serial
  Serial.print("Temp: "); Serial.print(temperature);
  Serial.print("  Humi: "); Serial.print(humidity);
  Serial.print("  Rain: "); Serial.print(rainValue);
  Serial.print("  Light: "); Serial.println(lightValue);

  // Ưu tiên: Dừng motor nếu chạm công tắc hành trình
  if (digitalRead(switch1Pin) == LOW || digitalRead(switch2Pin) == LOW) {
    stopMotor();
  }

  if (digitalRead(menuButton) == LOW) {
    currentMode = MODE_MENU;
    menu();
    delay(500);
  }

  switch (currentMode) {
    case MODE_MENU:
      if (digitalRead(aButton) == LOW) {
        currentMode = MODE_AUTO;
        delay(300);
      } else if (digitalRead(bButton) == LOW) {
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

      if (digitalRead(bButton) == LOW && digitalRead(switch2Pin) == HIGH) {
        right(); // Mở ra nếu chưa chạm switch2
      } 
      else if (digitalRead(aButton) == LOW && digitalRead(switch1Pin) == HIGH) {
        left();  // Thu vào nếu chưa chạm switch1
      } 
      else {
        stopMotor(); // Ngừng nếu không nhấn nút hoặc đã chạm công tắc
      }
      break;
  }

  delay(1000);
}

