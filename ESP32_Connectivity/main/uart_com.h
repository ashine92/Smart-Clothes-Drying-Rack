#ifndef UART_COM_H
#define UART_COM_H

#include <HardwareSerial.h>

extern HardwareSerial mySerial;

void initUART();
void requestSensorData();

#endif
