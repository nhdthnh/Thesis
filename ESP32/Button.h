#include <WiFiClient.h>
#include <HTTPUpdate.h>

const byte buttonPin[3] = {13, 12, 14};
bool buttonState[3] = {false, false, false};

void setupButton() {
  for (byte i = 0; i < 3; i++)
    pinMode(buttonPin[i], INPUT);
}

String getChipId() {
  String ChipIdHex = String((uint32_t)(ESP.getEfuseMac() & 0xFFFFFFFF), HEX); 
  ChipIdHex += String((uint32_t)(ESP.getEfuseMac() >> 32), HEX);             
  return ChipIdHex;
}

void update() {
  String url = "http://otadrive.com/deviceapi/update?";
  url += "k=09197499-fc37-4267-ada6-83a102ac29de";
  url += "&v=1.0.0.2";
  url += "&s=" + getChipId();
  WiFiClient client;
  httpUpdate.update(client, url, "1.0.0.2");
  Serial.println(url);
}

void checkButton() {
  static bool preButtonState[3] = {false, false, false};

  for (byte i = 0; i < 3; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
    if (preButtonState[i] == 1 && buttonState[i] == 0) {
           if (i == 0) changeScreen();
      else if (i == 1) {
        wm.resetSettings();
        delay(1000);
        ESP.restart();
      }
      else if (i == 2) 
      {
        clearLC();
        displayLC(1,"CHECKING");
        displayLC(2,"UPDATE");
        update();
        clearLC();
        displayLC(1,"COMPLETE");
      }
    }
    preButtonState[i] = buttonState[i];
  }
}