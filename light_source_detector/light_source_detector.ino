#define PHOTO_SENSOR_PIN1 A1
#define PHOTO_SENSOR_PIN2 A2
#define LED_PIN1 12
#define LED_PIN2 13

unsigned long previousMillis = 0;
const long interval = 250;

void setup() { 
  Serial.begin(9600); 
  pinMode(LED_PIN1,OUTPUT);
  pinMode(LED_PIN2,OUTPUT);
} 
 
void loop() { 
  int lightValue1 = analogRead(PHOTO_SENSOR_PIN1)-180; 
  int lightValue2 = analogRead(PHOTO_SENSOR_PIN2)-50;
  unsigned long currentMillis = millis();
 
  if (lightValue1 > lightValue2 + 10 || lightValue2 > lightValue1 + 10) {
    
    if (lightValue1 > lightValue2 + 10){
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        digitalWrite(LED_PIN2,LOW);
        if (digitalRead(LED_PIN1) == HIGH) {
          digitalWrite(LED_PIN1, LOW);
        } else {
          digitalWrite(LED_PIN1, HIGH);
        }
        
      }
    } else{

        if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          digitalWrite(LED_PIN1,LOW);
          if (digitalRead(LED_PIN2) == HIGH) {
            digitalWrite(LED_PIN2, LOW);
          } else {
            digitalWrite(LED_PIN2, HIGH);
          }
      }
    }
  }

  if (lightValue1 <= lightValue2 + 10 && lightValue1 >= lightValue2 - 10) {
    digitalWrite(LED_PIN1, HIGH);
    digitalWrite(LED_PIN2, HIGH);
  }
  
}