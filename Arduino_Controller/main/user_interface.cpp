// user_interface.cpp
#include "user_interface.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD() {
  lcd.init();
  lcd.backlight();
}

void menu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Drying Rack");
  lcd.setCursor(0, 1);
  lcd.print("Select mode...");
}
