const byte warningPin = A3;

void setupWarning() {
  pinMode(warningPin, INPUT);
}

void checkWarning() {
  if (!connected) return;

  if (flameState) {
    buzzerOn();
    Serial.println("Fire");
    sendLoRa("2-0-F-1\n");
    sendLoRa("2-0-D\n");
    while (!digitalRead(warningPin)) {byte a = 1;}
    buzzerOff();
    sendLoRa("2-0-S\n");
    displaySensor();
    // delay(30000);
  }

  if (temperature > thresholdTemp || humidity > thresholdHumi || ppm > thresholdAQ) {
    byte count = 0;
    Serial.println("Temp: "+String(temperature)+" "+String(thresholdTemp));
    Serial.println("Humi: "+String(humidity)+" "+String(thresholdHumi));
    Serial.println("Air: "+String(ppm)+" "+String(thresholdAQ));
    sendLoRa("2-0-D");
    while (count++ < 10) {
      checkLoRa();
      buzzerOn();
      delay(1000);
      buzzerOff();
      delay(1000);
      if (digitalRead(warningPin)) {
        checkLoRa();
        buzzerOff();
        // delay(30000);
        break;
      }
    }
    sendLoRa("2-0-S\n");
    displaySensor();
  }

  buzzerOff();
}