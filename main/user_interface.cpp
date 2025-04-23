#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "user_interface.h"
#include <TimeLib.h>         // Include TimeLib to handle time functions


LiquidCrystal_I2C lcd(0x27, 20, 4);

void initLCD() {
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("He thong sao phoi!");
  delay(1500);
  lcd.clear();
}

void menu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Phim 1 - Menu");
  lcd.setCursor(0, 1);
  lcd.print("Phim 2 - Automatic");
  lcd.setCursor(0, 2);
  lcd.print("Phim 3 - Manual");
}

void automaticMode(float temperature, float humidity, bool isRaining, int lightValue) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MODE: AUTOMATIC");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C");

  lcd.setCursor(0, 2);
  lcd.print("Humid: ");
  lcd.print(humidity, 0);
  lcd.print(" %");

  lcd.setCursor(0, 3);
  lcd.print(isRaining ? "Troi mua" : "Troi khong mua");
}

void manualMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MODE: MANUAL");
  lcd.setCursor(0, 1);
  lcd.print("Phim 3: Day");
  lcd.setCursor(0, 2);
  lcd.print("Phim 4: Thu");
}
