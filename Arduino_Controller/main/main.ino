/*
#include "control.h"
#include "user_interface.h"
#include <SoftwareSerial.h>
#include <DHT.h>

#define menuButton 3
#define aButton 5
#define bButton 4

#define rainSensor A0
#define lightSensor A1
#define dhtPin 6
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

SoftwareSerial mySerial(12, 13); // TX=12, RX=13

// Hàm xử lý lệnh từ ESP32
void processCommand(String cmd) {
  if (cmd == "MO SAO: ON") {
    if (digitalRead(switch1Pin) == HIGH) {
      left();
      Serial.println("Command executed: MO SAO: ON (Moving left)");
    } else {
      stopMotor();
      Serial.println("Command received but stopped: MO SAO: ON (Hit switch1)");
    }
  } else if (cmd == "MO SAO: OFF") {
    if (digitalRead(switch2Pin) == HIGH) {
      right();
      Serial.println("Command executed: MO SAO: OFF (Moving right)");
    } else {
      stopMotor();
      Serial.println("Command received but stopped: MO SAO: OFF (Hit switch2)");
    }
  }
}

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
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
  
  // Gửi thông báo khởi động để xác nhận kết nối UART
  Serial.println("Arduino ready for UART communication");
  mySerial.println("ARDUINO:READY");
  delay(500);
}

void loop() {
  // Đọc giá trị từ các cảm biến
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  rainValue = analogRead(rainSensor);
  lightValue = analogRead(lightSensor);
  
  // Kiểm tra giá trị hợp lệ
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    temperature = 0;
    humidity = 0;
  }
  
  // Gửi dữ liệu qua UART
  mySerial.print("TEMP:");
  mySerial.print(temperature);
  mySerial.print(",HUMI:");
  mySerial.print(humidity);
  mySerial.print(",RAIN:");
  mySerial.print(rainValue);
  mySerial.print(",LUX:");
  mySerial.println(lightValue);

  // In ra Serial Monitor để kiểm tra
  Serial.print("Sent to ESP32: TEMP:");
  Serial.print(temperature);
  Serial.print(",HUMI:");
  Serial.print(humidity);
  Serial.print(",RAIN:");
  Serial.print(rainValue);
  Serial.print(",LUX:");
  Serial.println(lightValue);

  // Cho thời gian ESP32 xử lý dữ liệu
  delay(100);

  // Nhận lệnh từ ESP32 
  while (mySerial.available()) {
    String cmd = mySerial.readStringUntil('\n');
    cmd.trim();
    if (cmd.length() > 0) {
      Serial.println("ESP32 command: " + cmd);
      processCommand(cmd);
    }
  }

  // Ưu tiên: Dừng motor nếu chạm công tắc hành trình
  if (digitalRead(switch1Pin) == LOW || digitalRead(switch2Pin) == LOW) {
    stopMotor();
  }

  // Xử lý các nút nhấn để chuyển mode
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

  delay(1900); // Tổng thời gian delay khoảng 2 giây (100ms + 1900ms)
}
*/

/* ================ TEST UART ==================
#include <SoftwareSerial.h>

// Cấu hình SoftwareSerial
SoftwareSerial mySerial(12, 13); // TX=12, RX=13

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 2000; // Gửi mỗi 1 giây
int counter = 0;

void setup() {
  // Khởi tạo Serial để debug
  Serial.begin(9600);
  delay(500);
  Serial.println("Arduino starting...");
  
  // Khởi tạo SoftwareSerial để giao tiếp với ESP32
  mySerial.begin(9600);
  Serial.println("SoftwareSerial initialized");
  
  // Thiết lập LED built-in để chỉ báo trạng thái
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Kiểm tra xem có dữ liệu nhận từ ESP32 không
  if (mySerial.available()) {
    String receivedData = mySerial.readStringUntil('\n');
    receivedData.trim();
    
    Serial.print("Received from ESP32: ");
    Serial.println(receivedData);
    
    // Nháy LED để chỉ báo nhận được dữ liệu
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  // Gửi dữ liệu định kỳ đến ESP32
  unsigned long currentMillis = millis();
  if (currentMillis - lastSendTime >= sendInterval) {
    lastSendTime = currentMillis;
    
    String message = "ARDUINO:" + String(counter++);
    mySerial.println(message);
    Serial.print("Sent to ESP32: ");
    Serial.println(message);
  } 
  }*/

// =========== TEST FULL CODE + UART =============
#include <SoftwareSerial.h>
#include <DHT.h>
#include "control.h"
#include "user_interface.h"

#define menuButton 3
#define aButton 5
#define bButton 4

#define rainSensor A0
#define lightSensor A1
#define dhtPin 6
DHT dht(dhtPin, DHT11);

int motorA1 = 8;
int motorA2 = 9;
int switch1Pin = 11;
int switch2Pin = 10;

SoftwareSerial mySerial(12, 13); // TX=12, RX=13

enum Mode { MODE_MENU, MODE_AUTO, MODE_MANUAL, MODE_TIMER };
Mode currentMode = MODE_MENU;

float temperature, humidity;
int rainValue, lightValue;

// Biến điều khiển từ xa
bool remoteControl = false;
int remoteCmd = -1; // -1 = Không lệnh, 0 = right, 1 = left

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(menuButton, INPUT_PULLUP);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(switch1Pin, INPUT_PULLUP);
  pinMode(switch2Pin, INPUT_PULLUP);

  dht.begin();
  stopMotor();
  lcd.backlight();
  initLCD();
  menu();
  mySerial.println("ARDUINO:READY");
}

void loop() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  rainValue = analogRead(rainSensor);
  lightValue = analogRead(lightSensor);

  if (isnan(temperature) || isnan(humidity)) {
    temperature = 0;
    humidity = 0;
  }

  String data = "TEMP:" + String(temperature) + ",HUMI:" + String(humidity) +
                  ",RAIN:" + String(rainValue) + ",LUX:" + String(lightValue);
  mySerial.println(data);
  
  if (mySerial.available() > 0) {
    String cmd = mySerial.readStringUntil('\n');
    Serial.print("Received from ESP32 (V4) : ");
    Serial.println(cmd);
    if (cmd == "1") {
      remoteControl = true;
      remoteCmd = 1;
    }
    else if (cmd == "0") {
      remoteControl = true;
      remoteCmd = 0;
    } else {
      remoteControl = false;
      stopMotor();
    }

    // Nếu đang trong chế độ điều khiển từ xa -> ưu tiên xử lý trước
    if (remoteControl) {
      if (remoteCmd == 1 && digitalRead(switch1Pin) == HIGH) {
        left();
      } else if (remoteCmd == 0 && digitalRead(switch2Pin) == HIGH) {
        right();
      } else {
        stopMotor();
      }
    }
    return;
  }

  // if (digitalRead(switch1Pin) == LOW || digitalRead(switch2Pin) == LOW) stopMotor();

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
      }
      else if (digitalRead(bButton) == LOW) {
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
      if (digitalRead(bButton) == LOW && digitalRead(switch2Pin) == HIGH) right();
      else if (digitalRead(aButton) == LOW && digitalRead(switch1Pin) == HIGH) left();
      else stopMotor();
      break;
  }
  delay(2000);
}

/*
void processCommand(String cmd) {
  if (cmd == "1" && digitalRead(switch1Pin) == HIGH) left();
  else if (cmd == "0" && digitalRead(switch2Pin) == HIGH) right();
  else stopMotor();
}
*/

/*
// =========== TEST FULL CODE + UART + BLYNK
#include <SoftwareSerial.h>
#include <DHT.h>
#include "control.h"
#include "user_interface.h"

#define menuButton 3
#define aButton 5
#define bButton 4

#define rainSensor A0
#define lightSensor A1
#define dhtPin 6
DHT dht(dhtPin, DHT11);

int motorA1 = 8;
int motorA2 = 9;
int switch1Pin = 11;
int switch2Pin = 10;

SoftwareSerial mySerial(12, 13); // TX=12, RX=13

enum Mode { MODE_MENU, MODE_AUTO, MODE_MANUAL, MODE_TIMER };
Mode currentMode = MODE_MENU;

float temperature, humidity;
int rainValue, lightValue;

// Biến điều khiển từ xa
bool remoteControl = false;
int remoteCmd = -1; // -1 = không lệnh, 0 = right, 1 = left

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(menuButton, INPUT_PULLUP);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(switch1Pin, INPUT_PULLUP);
  pinMode(switch2Pin, INPUT_PULLUP);

  dht.begin();
  stopMotor();
  lcd.backlight();
  initLCD();
  menu();
  mySerial.println("ARDUINO:READY");
}

void loop() {
  // Nhận lệnh từ ESP32
  if (mySerial.available() > 0) {
    String cmd = mySerial.readStringUntil('\n');
    Serial.print("Received from ESP32 (V4) : ");
    Serial.println(cmd);

    if (cmd == "1") {
      remoteControl = true;
      remoteCmd = 1;
    }
    else if (cmd == "0") {
      remoteControl = true;
      remoteCmd = 0;
    }
    else {
      remoteControl = false;
      stopMotor();
    }
  }

  // Nếu đang trong chế độ điều khiển từ xa → ưu tiên xử lý trước
  if (remoteControl) {
    if (remoteCmd == 1 && digitalRead(switch1Pin) == HIGH) {
      left();
    } else if (remoteCmd == 0 && digitalRead(switch2Pin) == HIGH) {
      right();
    } else {
      stopMotor();
    }
    return; // bỏ qua phần xử lý bên dưới để không bị stopMotor
  }

  // Đọc dữ liệu cảm biến và gửi về ESP32
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  rainValue = analogRead(rainSensor);
  lightValue = analogRead(lightSensor);

  if (isnan(temperature) || isnan(humidity)) {
    temperature = 0;
    humidity = 0;
  }

  String data = "TEMP:" + String(temperature) + ",HUMI:" + String(humidity) +
                ",RAIN:" + String(rainValue) + ",LUX:" + String(lightValue);
  mySerial.println(data);

  // Dừng motor nếu công tắc giới hạn được nhấn
  if (digitalRead(switch1Pin) == LOW || digitalRead(switch2Pin) == LOW) {
    stopMotor();
  }

  // Xử lý nút menu
  if (digitalRead(menuButton) == LOW) {
    currentMode = MODE_MENU;
    menu();
    delay(300);
  }

  // Xử lý chế độ hoạt động
  switch (currentMode) {
    case MODE_MENU:
      if (digitalRead(aButton) == LOW) {
        currentMode = MODE_AUTO;
        delay(300);
      }
      else if (digitalRead(bButton) == LOW) {
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
      if (digitalRead(bButton) == LOW && digitalRead(switch2Pin) == HIGH) right();
      else if (digitalRead(aButton) == LOW && digitalRead(switch1Pin) == HIGH) left();
      else stopMotor();
      break;
  }
}
*/

  
