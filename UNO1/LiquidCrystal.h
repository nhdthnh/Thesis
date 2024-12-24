#include <LiquidCrystal_I2C.h>

const byte row = 4, col = 20;
LiquidCrystal_I2C lcd(0x27, col, row);
float updateLCRate = 2; // Hz

void clearLC() {
  for (byte i = 0; i < row; i++) {
    lcd.setCursor(0, i);
    for (byte j = 0; j < col; j++)
      lcd.print(" ");
  }
}

void displayLC(byte line, String s) {
  if (line < 1 || line > row) {
    Serial.println("Invalid line number.");
    return;
  }
  lcd.setCursor(0, line-1);
  lcd.print("                    ");
  lcd.setCursor(0, line-1);
  lcd.print(s);
}

void displaySensor() {
  displayLC(1, "Temp: "+String(temperature)+" C R1: "+String(relayState[0]?"Off":"On"));
  displayLC(2, "Humi: "+String(humidity)+" % R2: "+String(relayState[1]?"Off":"On"));
  displayLC(3, "AQ: "+String(ppm)+" ppm R3: "+String(relayState[2]?"Off":"On"));
  displayLC(4, "Flame: "+String(flameState?"Yes":"No")+" R4: "+String(relayState[3]?"Off":"On"));
}

void setupLC() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}