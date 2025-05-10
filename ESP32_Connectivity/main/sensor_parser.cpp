#include "sensor_parser.h"

void parseAndSendToBlynk(String data) {
  float temp, hum;
  int rain, lux;

  sscanf(data.c_str(), "TEMP:%f,HUMI:%f,RAIN:%d,LUX:%d", &temp, &hum, &rain, &lux);
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, rain);
  Blynk.virtualWrite(V3, lux);
}

// Điều khiển từ Blynk gửi lệnh xuống Arduino
BLYNK_WRITE(V4) {
  String cmd = param.asStr();
  extern HardwareSerial mySerial;
  mySerial.println(cmd);
}
