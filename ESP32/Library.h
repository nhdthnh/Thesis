// LiquidCrystal
void setupLC();
void clearLC();
void displayLC(byte line, String s);
void displayTime();
void changeScreen();

// Button
void setupButton();
void checkButton();

// Online
void setupOnline();

// Database
void setupDatabase();
void setIntDB(String url, int val);
int getIntDB(String url);

// LoRaSimple
void setupLoRa();
void sendLoRa(String s);
void processDataLoRa(String s);
void checkLoRa();

// Debug
void setupDebug();
void checkDebug();

// Procedure
void checkRequest();

// Buzzer
void buzzerOn();
void buzzerOff();
void setupBuzzer();

#include "Online.h"
#include "Button.h"
#include "LiquidCrystal.h"
#include "Database.h"
#include "Procedure.h"
#include "LoRaSimple.h"
#include "Debug.h"
#include "Buzzer.h"