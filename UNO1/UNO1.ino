#include <Arduino.h>

unsigned long now = 0;
bool connected = false, flameState = false;
long temperature = 0, humidity = 0, ppm = 0, thresholdTemp = 1000, thresholdHumi = 1000, thresholdAQ = 10000;

#include "Library.h"

void setup() {
  setupButton();
  setupWarning();
  setupRelay();
  setupBuzzer();
  setupDebug();
  setupLC();

  setupLoRa();
  
  clearLC();
  displayLC(1, "Connecting to");
  displayLC(2, "gateway...");
}

void loop() {
  now = millis();

  checkLoRa();
  checkButton();
  checkDHT();
  checkMQ135();
  checkFlame();
  checkDebug();
  updateRelay();
  if (!connected) return;

  checkSensorChange();
  checkWarning();

  // updateLC();
}
