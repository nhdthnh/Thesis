// Button
void setupButton();
void checkButton();

// Relay
void setupRelay();
void updateRelay();

// DHT
void checkDHT();

// Flame
void setupFlame();
void checkFlame();

// MQ135
void checkMQ135();

// LiquidCrystal
void clearLC();
void displayLC(byte line, String s);
void displaySensor();
void setupLC();
void updateLC();

// LoRa
void setupLoRa();
void sendLoRa(String s);
void processDataLoRa(String s);
void checkLoRa();

// Debug
void setupDebug();
void printDebug(String s);
void checkDebug();

// Buzzer
void setupBuzzer();
void buzzerOn();
void buzzerOff();

#include "Buzzer.h"
#include "Warning.h"
#include "Relay.h"
#include "Button.h"
#include "MQ135.h"
#include "Flame.h"
#include "LoRaSimple.h"
#include "Debug.h"
#include "DHT.h"
#include "LiquidCrystal.h"

void checkSensorChange() {
  static int preT = 0, preH = 0, preP = 0, preF = 0;

  if (preT != temperature) {
    displaySensor();
    sendLoRa("2-0-T-"+String(temperature)+"\n");
    preT = temperature;
  }

  if (preH != humidity) {
    displaySensor();
    sendLoRa("2-0-H-"+String(humidity)+"\n");
    preH = humidity;
  }

  if (preP != ppm) {
    displaySensor();
    sendLoRa("2-0-A-"+String(ppm)+"\n");
    preP = ppm;
  }

  if (preF != flameState) {
    displaySensor();
    sendLoRa("2-0-F-"+String(flameState)+"\n");
    preF = flameState;
  }
}