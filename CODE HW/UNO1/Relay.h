const byte relayPin[4] = {8, 9, 10, 11};
bool relayState[4] = {true, true, true, true};

void setupRelay() {
  for (byte i = 0; i < 4; i++) {
    pinMode(relayPin[i], OUTPUT);
  }
}

void updateRelay() {
  for (byte i = 0; i < 4; i++) {
    digitalWrite(relayPin[i], relayState[i]); 
  }
}