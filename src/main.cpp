//Libraries
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
 
 // Pinout
#define YAHOO_PIN 13
#define YAHOO_SWITCH 21

// Wifi credentials
const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";
const char* IFTTT_URL = "<IFTT_URL>";

// Functions declaration 
int ifttt_post();

int ifttt_post(){
  if(WiFi.status()== WL_CONNECTED){   // Check WiFi connection status

     HTTPClient http;
     http.begin(IFTTT_URL); // Specify destination for HTTP request
     http.addHeader("Content-Type", "text/plain"); //Specify content-type header

     int httpResponseCode = http.POST("post");   // Send the actual POST request

     if(httpResponseCode>0){
      Serial.println(httpResponseCode);   // Print return code
      return httpResponseCode;
     }else{
      Serial.print("Error on sending request: ");
      Serial.println(httpResponseCode);
      return httpResponseCode;
     }

     http.end();  //Free resources
  }
  else{
    Serial.println("Connection error");
    return -1;
  }
}


void setup() {

  Serial.begin(115200);
  pinMode(YAHOO_PIN,OUTPUT);
  pinMode(YAHOO_SWITCH,INPUT_PULLUP);

  //Wifi connection
  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
  }

  if(WiFi.status()== WL_CONNECTED){
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else{
    Serial.println("Not connected- Working without WIFI");
  }
}

void loop() {

  bool switch_yahoo = digitalRead(YAHOO_SWITCH);
  Serial.println(switch_yahoo);
  if (switch_yahoo== LOW){
    digitalWrite(YAHOO_PIN, HIGH);
    ifttt_post();
    delay(1000);
    digitalWrite(YAHOO_PIN, LOW);
    delay(200);
  }

delay(100);
}

