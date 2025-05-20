#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include "Config.h"
#include "Display.h"

ESP8266WiFiMulti wifiMulti;
WiFiClient wifiClient;
String ip = "(IP UNSET)";

String id() {
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  return macID;
}

void StartAPMode() {
  IPAddress apIP(192, 168, 4, 1);
  ip_="192.168.4.1";
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssidAP.c_str(), passwordAP.c_str());
  Serial.println("WiFi up in AP mode with name: " + ssidAP);
  AP_UP = true;
  showStatus("Connect to ESP_WiFi and go to "+ip_);
}

void StartCLIMode() {
  Serial.println("Trying to connect to Wi-Fi...");
  showStatus("Connecting Wi-Fi "+String(ssidCLI) + "  ...");
  WiFi.disconnect();
  wifiMulti.addAP(ssidCLI, passwordCLI);
  int count = 0;
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
    count++;
    if (count >= 3) {
      cant_connect_wifi = true;
      showStatus("Wi-Fi Failed");
      return;
    }
  }
  wifi_connected = true;
  cant_connect_wifi = false;
  Serial.println("Connected to Wi-Fi");
  showStatus("Wi-Fi Connected");
  WiFi.softAPdisconnect(true);
  AP_UP = false;
  Serial.println("Destroying Access Point " + ssidAP);
}

void WIFI_init(bool mode_ap) {
  if (mode_ap && !AP_UP) {
    StartAPMode();
    ip = WiFi.softAPIP().toString();
  } else {
    StartCLIMode();
    ip = WiFi.localIP().toString();
  }
  if (cant_connect_wifi && !AP_UP) {
    cant_connect_wifi = false;
    WIFI_init(true);
  } else if (cant_connect_wifi) {
    cant_connect_wifi = false;
    WiFi.softAPdisconnect(true);
    AP_UP = false;
    WIFI_init(true);
  }
  Serial.println("IP address: " + ip);
}

#endif