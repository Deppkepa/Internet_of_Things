#define PHOTO_SENSOR_PIN1 A1

void setup() {
  Serial.begin(9600);
  
}

void loop() {
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
  delay(100);
}
