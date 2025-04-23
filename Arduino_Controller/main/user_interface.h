#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

void initLCD();
void menu();
void automaticMode(float temperature, float humidity, bool isRaining, int lightValue);
void manualMode();
#endif
