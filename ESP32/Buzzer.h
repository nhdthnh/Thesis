const int buzzerPin = 5;

void buzzerOn() {
  // noTone(buzzerPin);
  digitalWrite(buzzerPin, 1);
}

void buzzerOff() {
  // tone(buzzerPin, 1000);
  digitalWrite(buzzerPin, 0);
}

void blinkBuzzer(){
  buzzerOn();
  delay(1000);
  buzzerOff();
}

void setupBuzzer() {
  pinMode(buzzerPin, OUTPUT);
  buzzerOff();
}