/*
#define BLYNK_TEMPLATE_ID "TMPL6nRRrEdJk"
#define BLYNK_TEMPLATE_NAME "SmartRacket"
#define BLYNK_AUTH_TOKEN "Vgw90965m5qrziPBnhwd-aNHzcrVxagf"

#include <HardwareSerial.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Tuyet Anh";
char pass[] = "tuyetanh2510";
char auth[] = "Vgw90965m5qrziPBnhwd-aNHzcrVxagf";

float temp = 0, hum = 0;
int rain = 0, light = 0;
bool connectionEstablished = false;
unsigned long lastDataReceived = 0;
const unsigned long dataTimeout = 10000; // 10 seconds timeout

HardwareSerial mySerial(2); // UART2

void setupWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  
  // Wait for connection with timeout
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && 
         millis() - startAttemptTime < 20000) {
    delay(500);
    Serial.print(".");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("WiFi connection FAILED");
  }
}

void setupBlynk() {
  Serial.println("Connecting to Blynk...");
  Blynk.begin(auth, ssid, pass);
  
  if (Blynk.connected()) {
    Serial.println("Connected to Blynk server");
  } else {
    Serial.println("Failed to connect to Blynk server");
  }
}

void processData(String data) {
  // Tách dữ liệu bằng dấu ','
  int tempIndex = data.indexOf("TEMP:");
  int humiIndex = data.indexOf("HUMI:");
  int rainIndex = data.indexOf("RAIN:");
  int luxIndex  = data.indexOf("LUX:");

  if (tempIndex >= 0 && humiIndex >= 0 && rainIndex >= 0 && luxIndex >= 0) {
    // Extract the data
    float temp = data.substring(tempIndex + 5, humiIndex - 1).toFloat();
    float hum = data.substring(humiIndex + 5, rainIndex - 1).toFloat();
    int rain = data.substring(rainIndex + 5, luxIndex - 1).toInt();
    int light = data.substring(luxIndex + 4).toInt();

    // Print for debugging
    Serial.println("Parsed values:");
    Serial.println("Temperature: " + String(temp) + "°C");
    Serial.println("Humidity: " + String(hum) + "%");
    Serial.println("Rain: " + String(rain));
    Serial.println("Light: " + String(light));

    // Send to Blynk
    Blynk.virtualWrite(V0, temp); // nhiệt độ
    Blynk.virtualWrite(V1, hum); // độ ẩm
    Blynk.virtualWrite(V3, rain); // mưa
    Blynk.virtualWrite(V2, light); // ánh sáng
    
    // Update last received time
    lastDataReceived = millis();
  } else {
    Serial.println("Invalid data format received: " + data);
  }
}

void receiveFromSerial() {
  if (mySerial.available()) {
    String data = mySerial.readStringUntil('\n');  
    data.trim();
    
    if (data.length() > 0) {
      Serial.println("[DEBUG] Received data: " + data);
      
      // Check if it's the initial ready message
      if (data == "ARDUINO:READY") {
        connectionEstablished = true;
        Serial.println("Arduino connection established!");
        return;
      }
      
      // Process sensor data
      if (data.indexOf("TEMP:") >= 0) {
        processData(data);
      }
    }
  }
  
  // Check for timeout
  if (connectionEstablished && millis() - lastDataReceived > dataTimeout) {
    Serial.println("[WARNING] No data received from Arduino for " + String(dataTimeout/1000) + " seconds");
    // You could add reconnection logic here if needed
  }
}

// Handle Blynk App button press for V4
BLYNK_WRITE(V4) {
  int value = param.asInt();
  if (value == 1) {
    mySerial.println("MO SAO: ON");
    Serial.println("Sent command: MO SAO: ON");
  } else {
    mySerial.println("MO SAO: OFF");
    Serial.println("Sent command: MO SAO: OFF");
  }
}

void checkWiFiStatus() {
  static unsigned long lastCheck = 0;
  
  // Check WiFi status every 30 seconds
  if (millis() - lastCheck > 30000) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi connection lost! Reconnecting...");
      WiFi.reconnect();
    }
    lastCheck = millis();
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n----- ESP32 Smart Racket System Starting -----");
  
  // Initialize UART connection with Arduino
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  Serial.println("UART initialized. Waiting for Arduino...");
  
  // Setup WiFi and Blynk
  setupWiFi();
  setupBlynk();
  
  // Wait for Arduino to establish connection
  unsigned long startWaitTime = millis();
  while (!connectionEstablished && millis() - startWaitTime < 5000) {
    if (mySerial.available()) {
      String data = mySerial.readStringUntil('\n');
      data.trim();
      if (data == "ARDUINO:READY") {
        connectionEstablished = true;
        Serial.println("Arduino connection established!");
        break;
      }
    }
    delay(100);
  }
  
  if (!connectionEstablished) {
    Serial.println("Warning: Arduino not responding within timeout period.");
  }
  
  Serial.println("----- Setup Complete -----");
}

void loop() {
  // Run Blynk
  Blynk.run();
  
  // Check for and process incoming data from Arduino
  receiveFromSerial();
  
  // Monitor WiFi status
  checkWiFiStatus();
  
  // Short delay
  delay(100);
}
*/

// ================TEST UART ==================
/*
#include <HardwareSerial.h>

// Cấu hình HardwareSerial cho UART2
HardwareSerial mySerial(2); // UART2

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 3000; // Gửi mỗi 1.5 giây
int counter = 0;
const int ledPin = 2; // LED tích hợp trên hầu hết các board ESP32

void setup() {
  // Khởi tạo Serial để debug
  Serial.begin(115200);
  delay(500);
  Serial.println("\n\n----- ESP32 UART Test -----");
  
  // Khởi tạo UART để giao tiếp với Arduino
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  Serial.println("UART initialized (RX=16, TX=17)");
  
  // Thiết lập LED để chỉ báo trạng thái
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  Serial.println("ESP32 ready to communicate!");
}

void loop() {
  // Kiểm tra xem có dữ liệu nhận từ Arduino không
  
  if (mySerial.available()) {
    String receivedData = mySerial.readStringUntil('\n');
    // receivedData.trim();
    
    Serial.print("Received from Arduino: ");
    Serial.println(receivedData);
    
    // Nháy LED để chỉ báo nhận được dữ liệu
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
  }
  
  // Gửi dữ liệu định kỳ đến Arduino
  unsigned long currentMillis = millis();
  if (currentMillis - lastSendTime >= sendInterval) {
    lastSendTime = currentMillis;
    
    String message = "ESP32:" + String(counter++);
    mySerial.println(message);
    Serial.print("Sent to Arduino: ");
    Serial.println(message);
  }
  }
*/

// ================ TEST FULL CODE + UART
#define BLYNK_TEMPLATE_ID "TMPL6nRRrEdJk"
#define BLYNK_TEMPLATE_NAME "SmartRacket"
#define BLYNK_AUTH_TOKEN "Vgw90965m5qrziPBnhwd-aNHzcrVxagf"

#include <HardwareSerial.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "Vgw90965m5qrziPBnhwd-aNHzcrVxagf";
char ssid[] = "Tuyet Anh";
char pass[] = "tuyetanh2510";

HardwareSerial mySerial(1);
BlynkTimer timer;

String sensorData = "";
bool waitingForResponse = false;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17

  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);

  timer.setInterval(2000L, requestSensorData);
}

void loop() {
  Blynk.run();
  timer.run();

  if (mySerial.available()) {
    sensorData = mySerial.readStringUntil('\n');
    sensorData.trim();
    Serial.println("Received from Arduino: " + sensorData);
    parseAndSendToBlynk(sensorData);
    waitingForResponse = false;
  }
}

void requestSensorData() {
  if (!waitingForResponse) {
    // mySerial.println("REQUEST:SENSOR_DATA");
    waitingForResponse = true;
  }
}

void parseAndSendToBlynk(String data) {
  float temp, hum;
  int rain, lux;

  sscanf(data.c_str(), "TEMP:%f,HUMI:%f,RAIN:%d,LUX:%d", &temp, &hum, &rain, &lux);
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, rain);
  Blynk.virtualWrite(V3, lux);
}

BLYNK_WRITE(V4) {
  String cmd = param.asStr();
  mySerial.println(cmd);
}
