#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

const byte row = 2, col = 16;
LiquidCrystal_I2C lcd(0x27, col, row);
byte screen = 0; // 0 - wifi, 1 - time

void setupLC() {
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
}

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

String convertMonth(String s) {
       if (s == "January")   return "01";
  else if (s == "Febuary")   return "02";
  else if (s == "March")     return "03";
  else if (s == "Aprl")      return "04";
  else if (s == "May")       return "05";
  else if (s == "June")      return "06";
  else if (s == "July")      return "07";
  else if (s == "August")    return "08";
  else if (s == "September") return "09";
  else if (s == "October")   return "10";
  else if (s == "November")  return "11";
  else if (s == "December")  return "12";
}

void displayTime() {
  const char* ntpServer = "pool.ntp.org";
  const long  gmtOffset_sec = 25200;
  const int   daylightOffset_sec = 0;

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    clearLC();
    displayLC(1, "Failed to");
    displayLC(2, "obtain time");
    return;
  }

  char day[4], date[3], mon[10], year[5], hour[3], min[3], sec[3];
  strftime(day,   4, "%A", &timeinfo);
  strftime(date,  3, "%d", &timeinfo);
  strftime(mon,  10, "%B", &timeinfo);
  strftime(year,  5, "%Y", &timeinfo);
  strftime(hour,  3, "%H", &timeinfo);
  strftime(min,   3, "%M", &timeinfo);
  strftime(sec,   3, "%S", &timeinfo);

  String row1 = String(day[0])+String(day[1])+String(day[2])+", "+date+"/"+convertMonth(mon)+"/"+year[2]+year[3];
  String row2 = String(String(hour).toInt()%12<10?"0":"")+String(String(hour).toInt()%12)+":"+min+":"+sec+" "+(String(hour).toInt()>11?"PM":"AM");
  clearLC();
  displayLC(1, row1);
  displayLC(2, row2);
  Serial.println(row1);
  Serial.println(row2);
}

void changeScreen() {
  screen = screen == 0 ? 1 : 0;

  clearLC();

  if (screen == 0) {
    displayLC(1, String(WiFi.SSID().c_str()));
    displayLC(2, WiFi.localIP().toString());
  } else {
    clearLC();
    displayLC(1, "Getting time...");
    displayTime();
  }
}