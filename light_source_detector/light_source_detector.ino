#define PHOTO_SENSOR_PIN1 A1
#define PHOTO_SENSOR_PIN2 A2
#define LED_PIN1 13
#define LED_PIN2 12

int calibr=165;
bool blink_1,blink_2,blinking=true,true,true;
unsigned long int sum=0, i=0;
int ex=10;

void setup() { 
  Serial.begin(9600); 
  pinMode(LED_PIN1,OUTPUT);
  pinMode(LED_PIN2,OUTPUT);
} 

void blink(){
  if (blinking){
    if (blink_1){
      return;
    }
    if (blink_2){
      return;
    }
  } else {
    digitalWrite(LED_PIN1,HIGH);
    digitalWrite(LED_PIN2,HIGH);
  }
}
 
void loop() { 
  int photo_val1 = analogRead(PHOTO_SENSOR_PIN1)-180; 
  int photo_val2 = analogRead(PHOTO_SENSOR_PIN2)-30;
  
  if (photo_val1>=photo_val2 && abs(photo_val1-photo_val2)>ex){
      blink_1=true;
      blink_2=false;
      blinking=true;
  } else if(photo_val2>=photo_val1 && abs(photo_val1-photo_val2)>ex){
    blink_2=true;
    blink_1=false;
    blinking=true;
  } else{
    blink_1,blink_2,blinking=false,false,false;
  }
  blink();  
  
}