#define PHOTO_SENSOR_PIN1 A7

void setup() {
  Serial.begin(9600);
  
}
void process_state(){
  if (Serial.available()>0){
    char cmd = Serial.read();
    if (cmd == 'p'){
      int photo_val = analogRead(PHOTO_SENSOR_PIN1);
      // Serial.print("Photo val = ");
      // Serial.print(photo_val);
      // Serial.print("\n");
      if(photo_val>=1000){
        Serial.print(photo_val);
      } else if(photo_val<10){
        Serial.print(0);
        Serial.print(0);
        Serial.print(0);
        Serial.print(photo_val);
      } else if(photo_val<100){
        Serial.print(0);
        Serial.print(0);
        Serial.print(photo_val);
      } else if(photo_val<1000){
        Serial.print(0);
        Serial.print(photo_val);
      }
    }
  }
}
void loop() {
  process_state();
}
