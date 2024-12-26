#include<EEPROM.h>
#define no_internet 0
#define no_internet_interval 2000

#define internet_broker 1
#define internet_broker_interval 1500

#define only_internet 2
#define only_internet_interval 500

void clear_EEPROM() {
  EEPROM.begin(512);
  for (int i = 0; i < 512; i++) { EEPROM.write(i, 0); }
  EEPROM.end();
}

void writeStringToEEPROM(int address, String str) {
    for (int i = 0; i < str.length(); i++) {
        EEPROM.write(address + i, str[i]);
    }
    EEPROM.write(address + str.length(), '*');
}

String readStringFromEEPROM(int address, int length) {
    String result = "";
    char ch;
    for (int i = 0; i < length; i++) {
        ch = EEPROM.read(address + i);
        if (ch == '*') break;
        result += ch;
    }
    return result;
}

String ssidAP = "ESP_WIFI";
String passwordAP = "ESP8266123"; 

const char* ssidCLI = "";
const char* passwordCLI = "";

char* mqtt_broker = "test.mosquitto.org";//"broker.emqx.io";

bool wifi_connected=false;
bool mqtt_connected=false;
bool AP_UP=false;
bool cant_connect_wifi=false;

int state=no_internet;

const int mqtt_port = 1883;

const int led = 2;
int ledState = HIGH;
