bool oneReady = false, twoReady = false;

void setupLoRa() {
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
}

void sendLoRa(String s) {
  Serial2.print(s);
}

void processDataLoRa(String s) {
  if (s == "1-0-LOCATION 1 ONLINE") { 
    requestPhase = 2;
    setIntDB(oneURL+"/status", 1);
    connected[0] = true;
    return;
  }
  else if (s == "2-0-LOCATION 2 ONLINE") {
    requestPhase = 4;
    setIntDB(twoURL+"/status", 1);
    connected[1] = true;
    return;
  }

  if (connected[0] && s.substring(0, 3) == "1-0") {
         if (s[4] == 'T') { setIntDB(oneURL+"/Sensor/temperature", s.substring(6, s.length()).toInt()); sensorPhase = 2; }
    else if (s[4] == 'H') { setIntDB(oneURL+"/Sensor/humidity", s.substring(6, s.length()).toInt());    sensorPhase = 4; }
    else if (s[4] == 'A') { setIntDB(oneURL+"/Sensor/mq135", s.substring(6, s.length()).toInt());       sensorPhase = 6; }
    else if (s[4] == 'F') { setIntDB(oneURL+"/Sensor/flame", s.substring(6, s.length()).toInt());       sensorPhase = 8; }
    else if (s[4] == 'R') { setIntDB(oneURL+"/Relay/device "+s[5], String(s[7]).toInt()); }
    else if (s[4] == 'D') { displayLC(1, "1 IS DANGER"); buzzerOn(); }
    else if (s[4] == 'S') { displayLC(1, String(WiFi.SSID().c_str())); buzzerOff(); }
  }
  else if (connected[1] && s.substring(0, 3) == "2-0") {
         if (s[4] == 'T') { setIntDB(twoURL+"/Sensor/temperature", s.substring(6, s.length()).toInt()); sensorPhase = 10; }
    else if (s[4] == 'H') { setIntDB(twoURL+"/Sensor/humidity", s.substring(6, s.length()).toInt());    sensorPhase = 12; }
    else if (s[4] == 'A') { setIntDB(twoURL+"/Sensor/mq135", s.substring(6, s.length()).toInt());       sensorPhase = 14; }
    else if (s[4] == 'F') { setIntDB(twoURL+"/Sensor/flame", s.substring(6, s.length()).toInt());       sensorPhase = 16; }
    else if (s[4] == 'R') { setIntDB(twoURL+"/Relay/device "+s[5], String(s[7]).toInt()); }
    else if (s[4] == 'D') { displayLC(2, "2 IS DANGER"); buzzerOn(); }
    else if (s[4] == 'S') { displayLC(2, WiFi.localIP().toString()); buzzerOff(); }
  }
}

void checkLoRa() {
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.println("Received from lora: "+data);
    processDataLoRa(data);
  }
}