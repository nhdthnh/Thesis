const byte buzzerPin = A2;

void buzzerOn() {
  // noTone(buzzerPin);
  analogWrite(buzzerPin, 0);
}

void buzzerOff() {
  // tone(buzzerPin, 1000);
  analogWrite(buzzerPin, 255);
}

void setupBuzzer() {
  pinMode(buzzerPin, OUTPUT);
  buzzerOff();
}

