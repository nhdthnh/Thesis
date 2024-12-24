#include <DHT11.h>

const byte dhtPin = 12;
DHT11 dht(dhtPin);

long preDHT = 0;
float dhtRate = 0.2;

void checkDHT() {
  if (now - preDHT >= 1000 / dhtRate) {
    preDHT = now;
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    // printDebug("Temperature: "+String(temperature));
    // printDebug("Humidity: "+String(humidity));
  }
}