const byte warningPin = A3;

void setupWarning() {
  pinMode(warningPin, INPUT);
 
}

void checkWarning() {
  if (!connected) return;

  if (flameState) {
    buzzerOn();
    Serial.println("Fire");
    clearLC();
    displayLC(1, "DETECT");
    displayLC(2, "FIRE");
    sendLoRa("1-0-F-1\n");
    sendLoRa("1-0-D\n");
    checkLoRa();
    while (!digitalRead(warningPin)) {byte a = 1;}
    buzzerOff();
    sendLoRa("1-0-S\n");
    displaySensor();
    delay(10000);
  }

  if (temperature > thresholdTemp || humidity > thresholdHumi || ppm > thresholdAQ) {
    checkLoRa();
    byte count = 0;
    Serial.println("Temp: "+String(temperature)+" "+String(thresholdTemp));
    Serial.println("Humi: "+String(humidity)+" "+String(thresholdHumi));
    Serial.println("Air: "+String(ppm)+" "+String(thresholdAQ));
    sendLoRa("1-0-D");
    checkLoRa();
    while (count++ < 5) {
      checkLoRa();
      buzzerOn();
      delay(1000);
      buzzerOff();
      delay(1000);
      if (digitalRead(warningPin)) {
        Serial.println("WARNING BUTTON PRESSED");
        checkLoRa();
        buzzerOff();
        sendLoRa("1-0-S\n");
        delay(30000);
        break;
      }
    }
    sendLoRa("1-0-S\n");
    displaySensor();
  }
  buzzerOff();
}