const byte flamePin = 13;

void setupFlame() {
  pinMode(flamePin, INPUT);
}

void checkFlame() {
  flameState = digitalRead(flamePin) == 0;
}