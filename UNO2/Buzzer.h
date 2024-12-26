const byte buzzerPin = A2;

void buzzerOn() {
  // noTone(buzzerPin);
  analogWrite(buzzerPin, 0);
  // digitalWrite(buzzerPin,1);
}

void buzzerOff() {
  // tone(buzzerPin, 1000);
  analogWrite(buzzerPin, 255);
  //digitalWrite(buzzerPin, 0);
}

void setupBuzzer() {
  pinMode(buzzerPin, OUTPUT);
  buzzerOff();
}
