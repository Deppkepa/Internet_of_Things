#define LED_PIN1 13
#define LED_PIN2 12
#define LED_PIN3 10


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN1, OUTPUT); 
  pinMode(LED_PIN2, OUTPUT); 
  pinMode(LED_PIN3, OUTPUT); 
}



void loop() {
  
  digitalWrite(LED_PIN1, HIGH);    // включаем светодиод
	delay(10000);                   // ждем 1000 миллисекунд (1 секунда)
	digitalWrite(LED_PIN1, LOW); 

  digitalWrite(LED_PIN2, HIGH); 
  delay(1000);                   // ждем 1000 миллисекунд (1 секунда)
	digitalWrite(LED_PIN2, LOW);     // выключаем светодиод

  digitalWrite(LED_PIN3, HIGH); 
  delay(7000);                   // ждем 1000 миллисекунд (1 секунда)
	digitalWrite(LED_PIN3, LOW); 

  digitalWrite(LED_PIN2, HIGH); 
  delay(1000);                   // ждем 1000 миллисекунд (1 секунда)
	digitalWrite(LED_PIN2, LOW);
}
