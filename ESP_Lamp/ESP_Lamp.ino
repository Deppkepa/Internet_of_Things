#include "Config.h"
#include <EEPROM.h>
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"

unsigned long previousMillis = 0;
unsigned long currentMillis = millis();


int blinkCount = 0;
const int totalBlinks = 2;  

unsigned long blinkStartTime = 0;

void setup(void){
  Serial.begin(115200);
  EEPROM.begin(512);
  String name;
  String password;
  byte first;
  EEPROM.get(0,first);
  name=readStringFromEEPROM(21,32);
  password=readStringFromEEPROM(210,32);
  ssidCLI=name.c_str();
  passwordCLI=password.c_str();
  EEPROM.end();
  if (ssidCLI!="" && passwordCLI!="" && first==0xAA){
    
    WIFI_init(false);
  } else{
    WIFI_init(true);
  }
  server_init();
  
  
  pinMode(led,OUTPUT);
  
}   

void manage_led(){
  switch(state){
    case internet_broker:
      if (currentMillis - previousMillis >= internet_broker_interval) {        
        previousMillis = currentMillis;
        blinkStartTime = currentMillis;
      } else{
        if (blinkCount<totalBlinks*2+1 && currentMillis - blinkStartTime < 100 * 2) {
          if (currentMillis - blinkStartTime >= 100) {
            ledState = (blinkCount % 2 == 0) ? LOW : HIGH;
            digitalWrite(led, ledState);
            blinkCount++;
            blinkStartTime += 100;
          }
        } else {
          digitalWrite(led, ledState);
        }
      }
      
      break;
    case only_internet:
      if (currentMillis - previousMillis >= only_internet_interval){
        previousMillis=currentMillis;
        ledState=!ledState;
      }
      digitalWrite(led,ledState);
      break;
    case no_internet:
    default:
      if (currentMillis - previousMillis >= no_internet_interval){
        previousMillis=currentMillis;
        ledState=!ledState;
      }
      digitalWrite(led,ledState);
      break;
  }
  
}

void loop(void){
  server.handleClient(); 
  if (wifi_connected) { 
    if(mqtt_connected){
      state=internet_broker;
      mqtt_cli.loop();
    } else {
      state=only_internet;
      MQTT_init();
      mqtt_cli.publish("esp8266/state", "hello emqx");
      mqtt_cli.subscribe("esp8266/command");
    }
  } else {
    state=no_internet;
  }
  currentMillis = millis();
  manage_led();
}