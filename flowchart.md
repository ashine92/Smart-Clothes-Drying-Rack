# Smart Clothes Drying Rack - System Flowcharts

## 1. Main Program (Arduino Controller)
```mermaid
flowchart TD
    Start([Start]) --> DefineVars["Khai báo biến và thư viện:
    - DHT dht(dhtPin, DHT11)
    - SoftwareSerial mySerial(12, 13)
    - LiquidCrystal_I2C lcd(0x27, 16, 2)
    - Các chân cảm biến và động cơ"]
    
    DefineVars --> Setup["void setup()
    ------------------------
    1. Serial.begin(9600)
    2. mySerial.begin(9600)
    3. Cài đặt pinMode
    4. dht.begin()
    5. initLCD()
    6. menu()"]
    
    Setup --> Loop["void loop()"]
    
    Loop --> ReadSensors["readSensors():
    - Đọc nhiệt độ/độ ẩm
    - Đọc cảm biến mưa
    - Đọc cảm biến ánh sáng"]
    
    ReadSensors --> SendESP32["Gửi dữ liệu sang ESP32:
    TEMP:xx,HUMI:xx,RAIN:xx,LUX:xx"]
    
    SendESP32 --> CheckRemote{"Có lệnh từ
    ESP32?"}
    
    CheckRemote -->|Yes| HandleRemote["handleRemoteCommand()"]
    CheckRemote -->|No| CheckMenu{"Nút Menu
    được nhấn?"}
    
    HandleRemote --> CheckMode
    CheckMenu -->|Yes| ShowMenu["menu()"]
    CheckMenu -->|No| CheckMode{"Chế độ hiện tại?"}
    
    ShowMenu --> CheckMode
    
    CheckMode -->|MODE_MENU| HandleMenu["Xử lý lựa chọn menu:
    - Nút A -> MODE_AUTO
    - Nút B -> MODE_MANUAL"]
    
    CheckMode -->|MODE_AUTO| HandleAuto["automaticMode():
    - Kiểm tra thời tiết
    - Di chuyển giàn phơi"]
    
    CheckMode -->|MODE_MANUAL| HandleManual["manualMode():
    - Điều khiển bằng nút
    - Kiểm tra công tắc hành trình"]
    
    HandleMenu --> Delay
    HandleAuto --> Delay
    HandleManual --> Delay
    
    Delay["delay(2000)"] --> Loop
```

## 2. Motor Control Function
```mermaid
flowchart TD
    Start(["controlMotor()"]) --> CheckSwitch{"Kiểm tra công tắc
    hành trình"}
    
    CheckSwitch -->|"switch1Pin HIGH"| Left["left():
    motorA1 = HIGH
    motorA2 = LOW"]
    
    CheckSwitch -->|"switch2Pin HIGH"| Right["right():
    motorA1 = LOW
    motorA2 = HIGH"]
    
    CheckSwitch -->|"Cả hai LOW"| Stop["stopMotor():
    motorA1 = LOW
    motorA2 = LOW"]
    
    Left --> End([Return])
    Right --> End
    Stop --> End
```

## 3. Automatic Mode Function
```mermaid
flowchart TD
    Start(["automaticMode(temp, hum,
    isRaining, light)"]) --> CheckRain{"Trời mưa?
    rainValue < 500"}
    
    CheckRain -->|Yes| RetractRack["Thu giàn phơi:
    1. Kiểm tra switch1Pin
    2. left()"]
    
    CheckRain -->|No| CheckWeather{"Kiểm tra điều kiện:
    1. Nhiệt độ
    2. Độ ẩm
    3. Ánh sáng"}
    
    CheckWeather -->|"Điều kiện tốt"| ExtendRack["Mở giàn phơi:
    1. Kiểm tra switch2Pin
    2. right()"]
    
    CheckWeather -->|"Điều kiện xấu"| RetractRack
    
    RetractRack --> UpdateLCD["Cập nhật LCD:
    Hiển thị trạng thái"]
    ExtendRack --> UpdateLCD
    
    UpdateLCD --> End([Return])
```

## 4. Remote Control Handler
```mermaid
flowchart TD
    Start(["handleRemoteCommand(cmd)"]) --> ParseCmd{"Phân tích
    lệnh"}
    
    ParseCmd -->|"cmd = 1"| SetExtend["remoteControl = true
    remoteCmd = 1
    (Lệnh mở giàn phơi)"]
    
    ParseCmd -->|"cmd = 0"| SetRetract["remoteControl = true
    remoteCmd = 0
    (Lệnh thu giàn phơi)"]
    
    ParseCmd -->|"cmd khác"| ResetRemote["remoteControl = false
    remoteCmd = -1"]
    
    SetExtend --> CheckLimit{"Kiểm tra
    công tắc hành trình"}
    SetRetract --> CheckLimit
    ResetRemote --> End
    
    CheckLimit -->|"OK"| ControlMotor["Điều khiển động cơ
    theo lệnh"]
    CheckLimit -->|"Limit"| StopMotor["stopMotor()"]
    
    ControlMotor --> End([Return])
    StopMotor --> End
```

## 5. Sensor Reading Function
```mermaid
flowchart TD
    Start(["readSensors(temp, hum,
    rain, light)"]) --> ReadDHT["Đọc DHT11:
    temp = dht.readTemperature()
    hum = dht.readHumidity()"]
    
    ReadDHT --> CheckDHT{"DHT đọc
    thành công?"}
    
    CheckDHT -->|No| ResetDHT["temp = 0
    hum = 0"]
    CheckDHT -->|Yes| ReadAnalog
    
    ResetDHT --> ReadAnalog["Đọc cảm biến analog:
    rain = analogRead(rainSensor)
    light = analogRead(lightSensor)"]
    
    ReadAnalog --> End([Return])
```
