#ifndef SERVER_H
#define SERVER_H

#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "Config.h"
#include "WIFI.h"
#include "Display.h"

ESP8266WebServer server(80);

String readStringFromEEPROM(int addr, int len) {
  String data = "";
  for (int i = 0; i < len; i++) {
    char c = EEPROM.read(addr + i);
    if (c == 0) break;
    data += c;
  }
  return data;
}

void writeStringToEEPROM(int addr, String data, int len) {
  for (int i = 0; i < len; i++) {
    if (i < data.length()) {
      EEPROM.write(addr + i, data[i]);
    } else {
      EEPROM.write(addr + i, 0);
    }
  }
}

void handleRoot() {
  String s = "<!DOCTYPE html><html lang=\"en\"><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  s += "<title>ESP WiFi Setup</title>";
  s += "<style>";
  s += "body { font-family: Arial, sans-serif; max-width: 600px; margin: 0 auto; padding: 20px; background-color: #f5f5f5; }";
  s += "h1 { color: #333; text-align: center; }";
  s += "form { background-color: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1); }";
  s += "label { display: block; margin-bottom: 10px; font-weight: bold; color: #555; }";
  s += "input[type=\"text\"], input[type=\"password\"] { width: 100%; padding: 10px; margin-bottom: 15px; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box; }";
  s += "input[type=\"submit\"] { background-color: #4CAF50; color: white; padding: 12px 20px; border: none; border-radius: 4px; cursor: pointer; width: 100%; font-size: 16px; }";
  s += "input[type=\"submit\"]:hover { background-color: #45a049; }";
  s += "</style></head><body>";
  s += "<h1>ESP WiFi Setup</h1>";
  s += "<form action=\"/LED\" method=\"POST\">";
  s += "<label for=\"ssid\">SSID:</label>";
  s += "<input type=\"text\" id=\"ssid\" name=\"ssid\" required><br>";
  s += "<label for=\"pass\">Password:</label>";
  s += "<input type=\"password\" id=\"pass\" name=\"pass\" required><br>";
  s += "<label for=\"city\">City:</label>";
  s += "<input type=\"text\" id=\"city\" name=\"city\" value=\""+CITY+"\"><br>";
  s += "<input type=\"submit\" value=\"Submit\">";
  s += "</form></body></html>";
  server.send(200, "text/html", s);
}

void handleLED() {
  if (server.hasArg("ssid") && server.hasArg("pass")) {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");
    String city = server.arg("city");
    if (ssid.length() > 0 && pass.length() > 0 && city.length() > 0) {
      EEPROM.begin(512);
      writeStringToEEPROM(21, ssid, 32);
      writeStringToEEPROM(210, pass, 32);
      writeStringToEEPROM(250, city, 32);
      EEPROM.write(0, 0xAA);
      EEPROM.commit();
      EEPROM.end();
      ssidCLI = ssid.c_str();
      passwordCLI = pass.c_str();
      CITY=city;
      WEATHER_URL = "http://api.openweathermap.org/data/2.5/weather?q=" + CITY + "&appid=" + API_KEY + "&units=metric"+"&lang=en";
      server.send(200, "text/html", "WiFi settings saved. Rebooting...");
      delay(1000);
      ESP.restart();
    } else {
      server.send(200, "text/html", "Invalid input");
    }
  } else {
    server.send(200, "text/html", "Missing parameters");
  }
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}

void server_init() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/LED", HTTP_POST, handleLED);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

#endif