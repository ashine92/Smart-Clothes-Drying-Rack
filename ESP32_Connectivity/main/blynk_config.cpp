#include "blynk_config.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "DKT_LAU2";
char pass[] = "Daikientai";

BlynkTimer timer;
bool waitingForResponse = false;

void initWiFiAndBlynk() {
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);
}

void requestSensorData();

void setupTimer() {
  timer.setInterval(2000L, requestSensorData);
}
