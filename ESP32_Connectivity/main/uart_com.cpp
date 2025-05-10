#include "uart_com.h"
#include "blynk_config.h"

HardwareSerial mySerial(1); // UART1

void initUART() {
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
}

// Hàm gọi bởi timer từ blynk_config.cpp
void requestSensorData() {
  if (!waitingForResponse) {
    // Tùy vào thiết kế Arduino, có thể bật dòng này nếu cần yêu cầu trước
    // mySerial.println("REQUEST:SENSOR_DATA");
    waitingForResponse = true;
  }
}
