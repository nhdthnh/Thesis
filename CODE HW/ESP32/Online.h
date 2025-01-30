#include <WiFiManager.h>

WiFiManager wm;

void setupOnline() {

  clearLC();
  displayLC(1, "Connecting WiFi");
  displayLC(2, "................");

  bool res;
  // wm.resetSettings();
  wm.setTimeout(30);
  res = wm.autoConnect("ESP32");

  if (!res) {
    Serial.println("Failed to connect");
    ESP.restart();
  }  else {
    Serial.println("connected...yeey :)");
  }

  displayLC(1, "Connecting to");
  displayLC(2, "Firebase... ");
}