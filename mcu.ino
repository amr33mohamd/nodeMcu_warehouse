#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>

const char* ssid = "we are all Makers";
const char* password = "disha@2022";
String str;

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.1.10:8000/api";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200); 
Serial1.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
//  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
 // Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName + "/check/new-orders";
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
//        Serial.print("HTTP Response code: ");
//        Serial.println(httpResponseCode);
        String payload = http.getString();
          JSONVar myObject = JSON.parse(payload);
          Serial.print(myObject);
          Serial.print('|');
//if (myObject.hasOwnProperty("orders")) {
//      Serial.print("orders");
//      Serial.print((int) myObject["orders"]);
//      
////    Serial.print((const char*) myObject["orders"]);
////    Serial.print("|");
//  }

      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
