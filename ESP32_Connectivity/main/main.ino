#include "blynk_config.h"
#include "uart_comm.h"
#include "sensor_parser.h"

void setup() {
  Serial.begin(115200);
  initUART();
  initWiFiAndBlynk();
  setupTimer();
}

void loop() {
  Blynk.run();
  timer.run();

  // Xử lý dữ liệu nhận từ Arduino
  if (mySerial.available()) {
    String data = mySerial.readStringUntil('\n');
    data.trim();
    Serial.println("Received from Arduino: " + data);
    parseAndSendToBlynk(data);
    waitingForResponse = false;
  }
}
