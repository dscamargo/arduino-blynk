#include "config.h"

BLYNK_WRITE(V5) {
  int pinData = param.asInt();
  Serial.println(pinData);
  if (pinData == 0){
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }
}

void setup(){
  Blynk.begin(TOKEN_AUTH, WIFI_SSID, WIFI_PASS);  
  pinMode(2, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  Blynk.run();
}
