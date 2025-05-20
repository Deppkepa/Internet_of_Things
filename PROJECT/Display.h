#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include "Config.h"
#include "WeatherIcons.h"

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
  tft.setCursor(10, 50);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_YELLOW);
  tft.println(status);
}

void drawWeatherIcon(String weatherMain, int x, int y) {
  const uint16_t* iconData;
  
  if (weatherMain == "Clear") {
    iconData = sunnyIcon;
  } else if (weatherMain == "Clouds") {
    iconData = cloudyIcon;
  } else if (weatherMain == "Rain") {
    iconData = rainIcon;
  } else if (weatherMain == "Snow") {
    iconData = snowIcon;
  } else if (weatherMain == "Thunderstorm") {
    iconData = thunderstormIcon;
  } else {
    iconData = cloudyIcon;
  }
  
  tft.drawRGBBitmap(x, y, iconData, ICON_WIDTH, ICON_HEIGHT);
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
  float windSpeed = doc["wind"]["speed"];
  String weatherMain = doc["weather"][0]["main"];
  int pressure = doc["main"]["pressure"];
  String weatherDesc = doc["weather"][0]["description"];

  tft.fillScreen(ST77XX_BLACK);

  
  tft.setCursor(5, 5);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_CYAN); 
  tft.println(city);

  
  drawWeatherIcon(weatherMain, 5, 25);

  
  tft.setCursor(60, 30);
  tft.setTextSize(3); 
  if (temp >= 0) {
    tft.setTextColor(ST77XX_RED); 
  } else {
    tft.setTextColor(ST77XX_BLUE); 
  }
  tft.println(String(temp, 1) + "C");

  
  tft.setCursor(5, 75);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.println(weatherDesc);

  
  tft.setCursor(5, 90);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN); 
  tft.println("Hum: " + String(humidity) + "%");

  tft.setCursor(5, 100);
  tft.println("Pres: " + String(pressure) + "hPa");

  tft.setCursor(5, 110);
  tft.println("Wind: " + String(windSpeed) + "m/s");
}

#endif