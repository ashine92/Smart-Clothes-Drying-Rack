#include "connectivity.h"

void setup() {
  Serial.begin(9600);
  setupWiFi();
  setupBlynk();
}

void loop() {
  Blynk.run();
  receiveFromSerial();
  sendToBlynk();
  delay(1000);
}
