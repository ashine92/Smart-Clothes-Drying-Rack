// sensor.cpp
#include "sensor.h"
#include <DHT.h>

extern int rainSensor;
extern int lightSensor;
extern DHT dht;

void readSensors(float &temp, float &hum, int &rain, int &light) {
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  rain = analogRead(rainSensor);
  light = analogRead(lightSensor);

  if (isnan(temp) || isnan(hum)) {
    temp = 0;
    hum = 0;
  }
}
