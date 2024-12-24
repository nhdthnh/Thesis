long prePrint = 0;
float printRate = 4;

void setupDebug() {
  Serial.begin(9600);
  Serial.println("Serial is online");
}

void checkDebug() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    Serial.println("Received from laptop: "+data);
    sendLoRa(data);
    setIntDB(oneURL+"/status", data.toInt());
  }

  if (now - prePrint >= 1000 / printRate) {
    prePrint = now;
  }
}