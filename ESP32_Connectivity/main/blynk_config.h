#ifndef BLYNK_CONFIG_H
#define BLYNK_CONFIG_H

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL6nRRrEdJk"
#define BLYNK_TEMPLATE_NAME "SmartRacket"
#define BLYNK_AUTH_TOKEN "Vgw90965m5qrziPBnhwd-aNHzcrVxagf"

extern BlynkTimer timer;
extern bool waitingForResponse;

void initWiFiAndBlynk();
void setupTimer();

#endif
