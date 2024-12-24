#include <SoftwareSerial.h>

SoftwareSerial lora(6, 7);

void setupLoRa() {
  lora.begin(9600);
}

void sendLoRa(String s) {
  lora.print(s);
}

void processDataLoRa(String s) {
  if (s == "0-2-Request 2") {
    sendLoRa("2-0-LOCATION 2 ONLINE\n");
    connected = true;
  }

       if (s.substring(0, 5) == "0-2-T") thresholdTemp = s.substring(6, s.length()).toInt();
  else if (s.substring(0, 5) == "0-2-H") thresholdHumi = s.substring(6, s.length()).toInt();
  else if (s.substring(0, 5) == "0-2-A") thresholdAQ = s.substring(6, s.length()).toInt();
  else if (s.substring(0, 5) == "0-2-R" && s.length() < 11) {
    relayState[String(s[5]).toInt()-1] = s[7] == '1';
    // Serial.println("relay "+String(s[5])+" state "+String(s[7]));
  }
}

void checkLoRa() {
  if (lora.available()) {
    String data = lora.readStringUntil('\n');
    Serial.println("Received from lora: "+data);
    processDataLoRa(data);
  }
}