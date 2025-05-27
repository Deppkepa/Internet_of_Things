#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <EEPROM.h>
#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "WeatherAPI.h"
#include "Display.h"

unsigned long previousMillis = 0;
unsigned long lastWeatherUpdate = 0;
String lastStatus = "";
int apiErrorCount = 0;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  initDisplay();
  showStatus("Starting...");

  String name = readStringFromEEPROM(21, 32);
  String password = readStringFromEEPROM(210, 32);
  String savedCity = readStringFromEEPROM(250, 32);
  byte first;
  EEPROM.get(0, first);
  EEPROM.end();
  if (savedCity!=""){
    CITY=savedCity;
    WEATHER_URL = "http://api.openweathermap.org/data/2.5/weather?q=" + CITY + "&appid=" + API_KEY + "&units=metric"+"&lang=en";
  }
  if (name != "" && password != "" && first == 0xAA) {
    ssidCLI = name.c_str();
    passwordCLI = password.c_str();
    WIFI_init(false); 
  } else {
    WIFI_init(true);
  }

  server_init();
}

void loop() {
  unsigned long currentMillis = millis();
  server.handleClient();

  if (AP_UP) {
    if (lastStatus != "Connect to ESP_WiFi and go to "+ip_) { 
      showStatus("Connect to ESP_WiFi and go to "+ip_);
      lastStatus = "Connect to ESP_WiFi and go to "+ip_;
    }
  } else if (!wifi_connected) {
    if (lastStatus != "No Internet") {
      showStatus("No Internet");
      lastStatus = "No Internet";
    }
    if (currentMillis - previousMillis >= 10000) { 
      previousMillis = currentMillis;
      WIFI_init(false);
    }
  } else {
    
    if (currentMillis - lastWeatherUpdate >= WEATHER_UPDATE_INTERVAL || lastWeatherUpdate == 0) {
      lastWeatherUpdate = currentMillis;
      String weatherData = fetchWeatherData();
      if (weatherData != "") {
        displayWeather(weatherData);
        lastStatus = ""; 
        apiErrorCount = 0;
      } else {
        if (lastStatus != "API Error") {
          showStatus("API Error");
          lastStatus = "API Error";          
        }
        apiErrorCount++;
        if (apiErrorCount >= MAX_API_ERRORS){
          showStatus("Too many API errors. Starting AP...");
          lastStatus = "Too many API errors. Starting AP...";
          apiErrorCount = 0;
          WIFI_init(true);
        }
      }
    }
  }
}
