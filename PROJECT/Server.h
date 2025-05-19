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
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  s += "<title>ESP WiFi Setup</title></head><body>";
  s += "<h1>ESP WiFi Setup</h1>";
  s += "<form action=\"/LED\" method=\"POST\">";
  s += "SSID: <input type=\"text\" name=\"ssid\"><br>";
  s += "Password: <input type=\"password\" name=\"pass\"><br>";
  s += "<input type=\"submit\" value=\"Submit\">";
  s += "</form></body></html>";
  server.send(200, "text/html", s);
}

void handleLED() {
  if (server.hasArg("ssid") && server.hasArg("pass")) {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");
    if (ssid.length() > 0 && pass.length() > 0) {
      EEPROM.begin(512);
      writeStringToEEPROM(21, ssid, 32);
      writeStringToEEPROM(210, pass, 32);
      EEPROM.write(0, 0xAA);
      EEPROM.commit();
      EEPROM.end();
      ssidCLI = ssid.c_str();
      passwordCLI = pass.c_str();
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