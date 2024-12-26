#include <ESP8266WebServer.h>

ESP8266WebServer server(80);    

void handleRoot() {                         
  server.send(200, 
              "text/html", 
              "<form action=\"/LED\" method=\"POST\"><input name='nam' type='text' placeholder='Enter WiFi name'><br><input name='pass' type='password' placeholder='Enter WiFi password'> <br><input type=\"submit\" value=\"Connect to WiFi\"></form>");
}

void handleLED() {  
  String name=server.arg("nam");  
  String password=server.arg("pass");
  
  ssidCLI=name.c_str();
  passwordCLI=password.c_str(); 
  clear_EEPROM();
  EEPROM.begin(512);
  EEPROM.put(0,0xAA);
  writeStringToEEPROM(21, name);
  writeStringToEEPROM(210, password);
  EEPROM.commit();
  EEPROM.end();

  WIFI_init(false);                       
  server.sendHeader("Location","/");
  server.send(303);
}

void handleSENSOR() {                          
  int data = digitalRead(led);
  server.send(200, "text/html", String(data));
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}

void server_init() {
  server.on("/", HTTP_GET, handleRoot);     
  server.on("/LED", HTTP_POST, handleLED);  
  server.on("/SENSOR", HTTP_GET, handleSENSOR);  
  server.onNotFound(handleNotFound);        

  server.begin();                          
  Serial.println("HTTP server started");    
}
