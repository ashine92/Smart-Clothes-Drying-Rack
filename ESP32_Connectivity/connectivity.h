
#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "YourSSID";
char pass[] = "YourPassword";
char auth[] = "YourBlynkToken";

float temp = 0, hum = 0;
int rain = 0, light = 0;
String inputString = "";

void setupWiFi() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void setupBlynk() {
  Blynk.begin(auth, ssid, pass);
}

void receiveFromSerial() {
  while (Serial.available()) {
    inputString = Serial.readStringUntil('\n');
    int tIndex = inputString.indexOf(',');
    int hIndex = inputString.indexOf(',', tIndex + 1);
    int rIndex = inputString.indexOf(',', hIndex + 1);

    temp = inputString.substring(0, tIndex).toFloat();
    hum = inputString.substring(tIndex + 1, hIndex).toFloat();
    rain = inputString.substring(hIndex + 1, rIndex).toInt();
    light = inputString.substring(rIndex + 1).toInt();
  }
}

void sendToBlynk() {
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, rain);
  Blynk.virtualWrite(V3, light);
}

#endif
