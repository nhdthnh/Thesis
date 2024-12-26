long prePrint = 0;
float printRate = 4;

void setupDebug() {
  Serial.begin(9600);
}

void printDebug(String s) {
  Serial.println(s);
}

void checkDebug() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    Serial.println("Received from laptop: " + data);
  }

  if (now - prePrint >= 1000 / printRate) {
    prePrint = now;
  }
}