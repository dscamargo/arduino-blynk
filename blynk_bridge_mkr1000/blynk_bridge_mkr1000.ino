#include "config.h";

#define BUTTON_PIN 4

float temperatura = 0;
bool current = false;
bool last = false;
boolean btnState = false;
char normTemp[50] = "";
BlynkTimer timer;
WidgetLED led1(V1);
WidgetBridge bridge1(V1);

BLYNK_CONNECTED() {
  // Place the AuthToken of the second hardware here
  bridge1.setAuthToken("f57f03f772544f3196147171ba3fdf8d"); 
}

BLYNK_WRITE(V5) {
  int pinData = param.asInt();
  Serial.println(pinData);
  bridge1.virtualWrite(V5, pinData);
}


void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  
  Blynk.virtualWrite(V0, normTemp);
  analogReading();
  notifyHighTemp();
  
}

void setup() {
  
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Blynk.begin(TOKEN_AUTH, WIFI_SSID, WIFI_PASS);

  timer.setInterval(1000L, myTimerEvent);

}

void loop() {
  Blynk.run();
  timer.run();
}

void colorLedTemperatura(){
  led1.on();
  if (temperatura <= 20){
    led1.setColor("#04C0F8"); // azul
  } else if (temperatura > 20 && temperatura <= 35){
    led1.setColor("#f2620e"); // laranja
  } else if (temperatura > 35){
    led1.setColor("#ff0000"); // vermelho
  }
}

void notifyHighTemp(){
  if (temperatura > 45){
    Serial.print("Temperatura alta: ");
    Serial.println(temperatura);
    Blynk.notify("Temperatura muito alta !!");
  } else {
    Serial.println("Temperatura OK");
  }
}

void buttonLedWidget(){
  boolean isPressed = (digitalRead(BUTTON_PIN) == LOW);
  if (isPressed != btnState){
    if(isPressed){
      led1.on();
    } else{
      led1.off();
    }
    btnState = isPressed;
  }
}

void analogReading(){
  analogReadResolution(16);  // Resolução de 16 bits (0 - 65536)
  int analogValue = analogRead(A1); // Valor AD
  temperatura = (3.3/65535.0)*analogValue*100; //LM35
  sprintf(normTemp,"%2.2f",temperatura);
  colorLedTemperatura();
}
