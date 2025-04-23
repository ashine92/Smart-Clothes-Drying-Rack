void left() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
}

void right() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
}

void stopMotor() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  //Serial.println("Stop Motor");
}