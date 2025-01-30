#include <Arduino.h>

const String oneURL = "/user/nhdthnh/LOCATION 1", twoURL = "/user/nhdthnh/LOCATION 2";
unsigned long now = 0;
bool connected[2] = {false, false}, serverOnline[2] = {false, false};
byte sensorPhase = -1;

#include "Library.h"

void setup() {
  setupButton();
  setupDebug();
  setupLC();
  setupBuzzer();
  setupOnline();
  setupDatabase();
  
  Serial.println(String(WiFi.SSID().c_str()));
  Serial.println(WiFi.localIP().toString());

  setupLoRa();
}

void loop() {
  now = millis();

  checkLoRa();
  checkDebug();
  checkButton();

  if (serverOnline[0] && serverOnline[1]) {
    checkRequest();
  }

  checkDatabase();
}
