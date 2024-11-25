#define PHOTO_SENSOR_PIN1 A2
#define PHOTO_SENSOR_PIN2 A1
#define PIN1 13
#define PIN2 12
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int photo_val1 = analogRead(PHOTO_SENSOR_PIN1);
  int photo_val2 = analogRead(PHOTO_SENSOR_PIN2);
  if (photo_val1+440 >= 500){
    digitalWrite(PIN1, HIGH);
    digitalWrite(PIN2, LOW);
  } 
  if (photo_val2 >= 500){
    digitalWrite(PIN1, LOW);
    digitalWrite(PIN2, HIGH);
  }
  if (photo_val2 <500 && photo_val1+440 <500) {
    digitalWrite(PIN1, LOW);
    digitalWrite(PIN2, LOW);
  }
  Serial.print("Photo val1 = ");
  Serial.print(photo_val1+440);
  Serial.print("\n");
  Serial.print("Photo val2 = ");
  Serial.print(photo_val2);
  
  Serial.print("\n");
  delay(500);
}

