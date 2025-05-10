// control.cpp
#include "control.h"
#include <Arduino.h>

extern int motorA1;
extern int motorA2;

void left() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
}

void right() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
}

void stopMotor() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
}

void automaticMode(float temp, float hum, bool isRaining, int light) {
  // logic tự động, có thể mở rộng
}

void manualMode() {
  // Hiện tại để trống nếu chưa cần xử lý riêng
}
