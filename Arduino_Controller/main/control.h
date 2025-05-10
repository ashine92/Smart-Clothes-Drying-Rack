// control.h
#ifndef CONTROL_H
#define CONTROL_H

void left();
void right();
void stopMotor();
void automaticMode(float temp, float hum, bool isRaining, int light);
void manualMode();

#endif
