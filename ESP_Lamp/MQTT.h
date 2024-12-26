#include <PubSubClient.h>

PubSubClient mqtt_cli(wifiClient);

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    if((char) payload[0]=='1'){
      ledState=LOW;

    } else{
      ledState=HIGH;
    }
    Serial.println();
    Serial.println("-----------------------");
}

void MQTT_init(){
  mqtt_cli.setServer(mqtt_broker, mqtt_port);
  mqtt_cli.setCallback(callback);
  
  String client_id = "esp8266-" + String(WiFi.macAddress());
  Serial.print("The client " + client_id);
  Serial.println(" connects to the public mqtt broker\n");
  if (mqtt_cli.connect(client_id.c_str())){
      Serial.println("MQTT Connected");
      mqtt_connected=true;
  } else {
      mqtt_connected=false;
      Serial.print("failed with state ");
      Serial.println(mqtt_cli.state());
    }
    
  
}
