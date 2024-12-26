const byte buttonPin[4] = { 5, 4, 3, 2 };
bool buttonState[4] = { false, false, false, false };
unsigned long prePress[4] = { 0, 0, 0, 0 };

void setupButton() {
  for (byte i = 0; i < 4; i++)
    pinMode(buttonPin[i], INPUT);
}

void checkButton() {
  static bool preButtonState[4] = { false, false, false, false };

  for (byte i = 0; i < 4; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
    if (preButtonState[i] == 1 && buttonState[i] == 0 && now - prePress[i] >= 300) {
      relayState[i] = !relayState[i];
      Serial.println("Button " + String(i) + " is pressed");
      prePress[i] = now;
      sendLoRa("2-0-R" + String(i + 1) + "-" + String(relayState[i]) + "\n");
      displaySensor();
    }
    if (preButtonState[i] == 0 && buttonState[i] == 1 && now - prePress[i] >= 300) {
      prePress[i] = now;
    }
    preButtonState[i] = buttonState[i];
  }
}