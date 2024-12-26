#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;    
WiFiClient wifiClient;

String ip = "(IP UNSET)"; 

String id(){
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  return macID;
}

void StartAPMode() {
  IPAddress apIP(192, 168, 4, 1);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP((ssidAP).c_str(), passwordAP.c_str());
  Serial.println("");
  Serial.println("WiFi up in AP mode with name: "+ ssidAP);
  AP_UP = true;
}

void StartCLIMode() {
  Serial.println();
  Serial.println("Trying to connect to someone's wifi");
  WiFi.disconnect();
  wifiMulti.addAP(ssidCLI, passwordCLI);
  int count=0;
  while(wifiMulti.run() != WL_CONNECTED ) {
    Serial.println("Connecting...");
    count+=1;
    if (count>=5){
      cant_connect_wifi=true;
      return;
    }
    
  }
  wifi_connected=true;
  cant_connect_wifi=false;
  Serial.println("Connected to some wifi");
  WiFi.softAPdisconnect (true);
  AP_UP=false;
  Serial.print("Destroing Access Point ");
  Serial.println(ssidAP);
  
}

void WIFI_init(bool mode_ap) {
  if (mode_ap && !AP_UP) {
    StartAPMode();
    ip = WiFi.softAPIP().toString();
  } else {
    StartCLIMode();
    ip = WiFi.localIP().toString();
  }
  if(cant_connect_wifi && !AP_UP){
    cant_connect_wifi=false;
    return WIFI_init(true);
  } else if(cant_connect_wifi){
    cant_connect_wifi=false;
    WiFi.softAPdisconnect (true);
    AP_UP=false;
    return WIFI_init(true);
  }
  Serial.println("IP address: ");
  Serial.println(ip);
}
