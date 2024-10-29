#define PHOTO_SENSOR_PIN1 A1 
#define PHOTO_SENSOR_PIN2 A2 
#define LED_PIN1 12 
#define LED_PIN2 13 
 
#define BLINK_INTERVAL 500 
 
bool blink_1=true,blink_2=true,blinking=true; 
unsigned long int sum=0, i=0; 
int ex=20; 
long int blink1_start,blink2_start; 
bool led1_status=LOW,led2_status=LOW; 
 
void setup() {  
  Serial.begin(9600);  
  pinMode(LED_PIN1,OUTPUT); 
  pinMode(LED_PIN2,OUTPUT); 
}  
 
void blink() {  
  unsigned long currentMillis = millis(); 
 
  // Проверяем, нужно ли моргать первым светодиодом 
  if (blink_1) {  
    if (currentMillis - blink1_start >= BLINK_INTERVAL) { 
      led1_status = !led1_status; // Меняем состояние LED 
      digitalWrite(LED_PIN1, led1_status ? HIGH : LOW); // Устанавливаем состояние LED 
      blink1_start = currentMillis; // Обновляем время последней смены состояния 
    } 
  } else { 
    digitalWrite(LED_PIN1, LOW); // Выключаем LED1, если не должно мигать 
  } 
 
  // Проверяем, нужно ли моргать вторым светодиодом 
  if (blink_2) { 
    if (currentMillis - blink2_start >= BLINK_INTERVAL) { 
      led2_status = !led2_status; // Меняем состояние LED 
      digitalWrite(LED_PIN2, led2_status ? HIGH : LOW); // Устанавливаем состояние LED 
      blink2_start = currentMillis; // Обновляем время последней смены состояния 
    } 
  } else { 
    digitalWrite(LED_PIN2, LOW); // Выключаем LED2, если не должно мигать 
  } 
  if(!blink_1 && !blink_2){ 
    digitalWrite(LED_PIN1,HIGH); 
    digitalWrite(LED_PIN2,HIGH); 
  } 
}  
  
void loop() {  
  int photo_val1 = analogRead(PHOTO_SENSOR_PIN1)-180;  
  int photo_val2 = analogRead(PHOTO_SENSOR_PIN2)-50; 
   
  if (photo_val1>=photo_val2 && abs(photo_val1-photo_val2)>ex){ 
      blink_1=true; 
      blink1_start=millis(); 
      blink_2=false; 
      blinking=true; 
  } else if(photo_val2>photo_val1 && abs(photo_val1-photo_val2)>ex){ 
    blink_2=true; 
    blink2_start=millis(); 
    blink_1=false; 
    blinking=true; 
  } else{ 
    blink_1=false; 
    blink_2=false; 
    blinking=false; 
  } 
  blink(); 
  Serial.println(photo_val1); 
  Serial.println(photo_val2);   
  //delay(1000); 
   
}