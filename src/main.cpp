#include <Arduino.h>

#define YAHOO_PIN 13
#define YAHOO_SWITCH 21

void setup() {

  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(YAHOO_PIN,OUTPUT);
  pinMode(YAHOO_SWITCH,INPUT_PULLUP);
}

void loop() {

  bool switch_yahoo = digitalRead(YAHOO_SWITCH);
  Serial.println(switch_yahoo);
  if (switch_yahoo== LOW){
    digitalWrite(YAHOO_PIN, HIGH);
    delay(1000);
    digitalWrite(YAHOO_PIN, LOW);
    delay(200);
  }

delay(100);
}