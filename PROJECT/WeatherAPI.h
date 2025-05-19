#ifndef WEATHER_API_H
#define WEATHER_API_H

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "Config.h"
#include "Display.h"

String fetchWeatherData() {
  if (!wifi_connected) {
    return "";
  }

  WiFiClient client;
  HTTPClient http;
  String payload = "";

  showStatus("Fetching Weather...");

  if (http.begin(client, WEATHER_URL)) {
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        payload = http.getString();
      }
    } else {
      Serial.printf("GET failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    Serial.println("Unable to connect to API");
  }

  return payload;
}

#endif