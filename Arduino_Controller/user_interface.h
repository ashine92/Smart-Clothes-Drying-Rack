
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <LiquidCrystal_I2C.h>
extern LiquidCrystal_I2C lcd;

void initLCD() {
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("He thong sao phoi!");
  delay(1000);
  lcd.clear();
}

void menu() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Phim 1 - Menu");
  lcd.setCursor(0, 1); lcd.print("Phim 2 - Automatic");
  lcd.setCursor(0, 2); lcd.print("Phim 3 - Manual");
  lcd.setCursor(0, 3); lcd.print("Phim 4 - Timer");
}

void automaticMode(float temperature, float humidity, int rain, int light) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("MODE: AUTOMATIC");
  lcd.setCursor(0, 1); lcd.print("Nhiet: "); lcd.print(temperature);
  lcd.setCursor(0, 2); lcd.print("Do am: "); lcd.print(humidity);
  lcd.setCursor(0, 3); lcd.print("Mua: "); lcd.print(rain);
}

void manualMode() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("MODE: MANUAL");
  lcd.setCursor(0, 1); lcd.print("D3 - Out");
  lcd.setCursor(0, 2); lcd.print("D4 - In");
}

void timerMode(int hourIn, int minIn, int hourOut, int minOut) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("MODE: TIMER");
  lcd.setCursor(0, 1); lcd.print("Thu: "); lcd.print(hourIn); lcd.print(":"); lcd.print(minIn);
  lcd.setCursor(0, 2); lcd.print("Mo: "); lcd.print(hourOut); lcd.print(":"); lcd.print(minOut);
}

#endif
