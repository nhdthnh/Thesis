unsigned long requestPhase = 0, preRequest = 0, preSensor = 0;

void checkRequest() {
  if (now - preRequest >= 10000) {
    // Serial.println("Timeout LoRa request phase"+String(requestPhase));
         if (requestPhase == 1) { setIntDB(oneURL+"/status", 0); requestPhase = 2; }
    else if (requestPhase == 3) { setIntDB(twoURL+"/status", 0); requestPhase = 4; }
  }

  if (requestPhase == 0) { 
    clearLC();
    displayLC(1, String(WiFi.SSID().c_str()));
    displayLC(2, WiFi.localIP().toString());
    sendLoRa("0-1-Request 1\n");
    requestPhase = 1;
    preRequest = now;
  }
  else if (requestPhase == 2) {
    sendLoRa("0-2-Request 2\n");
    requestPhase = 3;
    preRequest = now;
  }
}