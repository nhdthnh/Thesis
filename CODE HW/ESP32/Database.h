#include <FirebaseClient.h>
#include <WiFiClientSecure.h>

#define DATABASE_URL "https://webserver-948ed-default-rtdb.firebaseio.com/"

WiFiClientSecure ssl1, ssl2, ssl3;
DefaultNetwork network;
AsyncClientClass client1(ssl1, getNetwork(network)), client2(ssl2, getNetwork(network)), client3(ssl3, getNetwork(network));

FirebaseApp app;
RealtimeDatabase Database;
AsyncResult resultLocation1, resultLocation2, result3;
NoAuth noAuth;

void printResult(AsyncResult &aResult) {
  if (aResult.isDebug())
    Firebase.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());

  if (aResult.isError())
    Firebase.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());

  if (aResult.available()) {
    RealtimeDatabaseResult &RTDB = aResult.to<RealtimeDatabaseResult>();
    if (RTDB.isStream()) {
      Serial.println("----------------------------");

           if (aResult.uid() == resultLocation1.uid()) serverOnline[0] = true;
      else if (aResult.uid() == resultLocation2.uid()) serverOnline[1] = true;

      // Firebase.printf("task: %s\n", aResult.uid().c_str());
      // Firebase.printf("event: %s\n", RTDB.event().c_str());
      // Firebase.printf("path: %s\n", RTDB.dataPath().c_str());
      // Firebase.printf("data: %s\n", RTDB.to<const char *>());
      // Firebase.printf("type: %d\n", RTDB.type());

      String path = String(RTDB.dataPath().c_str()),
             data = RTDB.data(),
             target = aResult.uid() == resultLocation1.uid() ? "1" : "2";

      // Serial.println(path);
      // Serial.println(data);

      if (path == "/") { // lấy dữ liệu lần đầu
        sendLoRa("0-"+target+"-R1-"+data[data.indexOf("device 1")+10]+"\n");
        sendLoRa("0-"+target+"-R2-"+data[data.indexOf("device 2")+10]+"\n");
        sendLoRa("0-"+target+"-R3-"+data[data.indexOf("device 3")+10]+"\n");
        sendLoRa("0-"+target+"-R4-"+data[data.indexOf("device 4")+10]+"\n");

        data = data.substring(0, data.length()-1);
        String temp = data.substring(data.indexOf("temperatureThreshold")+22, data.lastIndexOf("}"));
        // data = data.substring(0, data.indexOf("temperatureMinThreshold"));
        String humi = data.substring(data.indexOf("humidityThreshold")+19, data.indexOf("temperatureMinThreshold")-2);
        // data = data.substring(0, data.indexOf("humidityMinThreshold")+5);
        String air = data.substring(data.indexOf("airQualityThreshold")+21, data.lastIndexOf("humidityMinThreshold")-2);
        sendLoRa("0-"+target+"-T-"+temp+"\n");
        sendLoRa("0-"+target+"-H-"+humi+"\n");
        sendLoRa("0-"+target+"-A-"+air+"\n");
      }
      // lấy dữ liệu khi database bị thay đổi
      else if (path.indexOf("/Relay/device") == 0)
        sendLoRa("0-"+target+"-R"+path[path.length()-1]+"-"+data+"\n");
      else if (path.indexOf("/Threshold/temperatureThreshold") == 0)
        sendLoRa("0-"+target+"-T-"+data.toInt()+"\n");
      else if (path.indexOf("/Threshold/humidityThreshold") == 0)
        sendLoRa("0-"+target+"-H-"+data.toInt()+"\n");
      else if (path.indexOf("/Threshold/airQualityThreshold") == 0)
        sendLoRa("0-"+target+"-A-"+data.toInt()+"\n");

    } else {
      Serial.println("----------------------------");
      Firebase.printf("task: %s, payload: %s\n", aResult.uid().c_str(), aResult.c_str());
    }
  }
}

void printError(int code, const String &msg) {
  Firebase.printf("Error, msg: %s, code: %d\n", msg.c_str(), code);
}

void setupDatabase() {
  ssl1.setInsecure();
  ssl2.setInsecure();
  ssl3.setInsecure();

  initializeApp(client1, app, getAuth(noAuth));
  initializeApp(client2, app, getAuth(noAuth));
  app.getApp<RealtimeDatabase>(Database);

  Database.url(DATABASE_URL);

  Database.get(client1, "/user/nhdthnh/LOCATION 1", resultLocation1, true /* this option is for Stream connection */);
  delay(2000);
  Database.get(client2, "/user/nhdthnh/LOCATION 2", resultLocation2, true /* this option is for Stream connection */);
  delay(2000);
}

int getIntDB(String url) {
  return Database.get<int>(client3, url);
}

void setIntDB(String url, int val) {
  Database.set<int>(client3, url, val, result3);
}

void checkDatabase() {
  Database.loop();
  printResult(resultLocation1);
  printResult(resultLocation2);
  printResult(result3);
}