#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include "Config.h"

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void initDisplay() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1); 
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
}

void showStatus(String status) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println(status);
}

void displayWeather(String weatherData) {
  if (weatherData == "") return;

  
  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, weatherData);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  
  const char* city = doc["name"];
  float temp = doc["main"]["temp"];
  int humidity = doc["main"]["humidity"];
  String weatherDesc = doc["weather"][0]["description"];

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println(city);
  tft.setTextSize(1);
  tft.println("Temp: " + String(temp) + " C");
  tft.println("Humidity: " + String(humidity) + "%");
  tft.println("Weather: " + weatherDesc);
}

#endif