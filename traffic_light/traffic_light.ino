#define LED_PIN1 13 //Зелёный
#define LED_PIN2 12 //Жёлтый (синий)
#define LED_PIN3 10 //Красный

#define COMMAND_MANUAL 'm' //команда на ручное управление
#define COMMAND_AUTO 'a' //команда на автоматическое управление

#define LED_RED 'r' //метка красного светодиода
#define LED_GREEN 'g' //метка зелёного светодиода

/*
Запрограммировать автоматический режим работы светофора:
 зеленый (10 с) - мигающий зеленый (2 с) - желтый (1с) - красный (7 с) - желтый (1с) - зеленый (10 с).
 Добавить возможность перевода на ручное управление через команду с ПК:
 запрос на перевод (одна команда) и режим в котором светофор будет работать зеленый или красный (вторая команда).
 Если текущий режим не соответствует запрошенному, сделать перевод в него через желтый (3с).
 Ограничить ручной режим на 60 секунд - далее происходит возврат к автоматическому режиму
 даже если запроса на возврат не было.
 В коде не должно быть задержек (delay).
*/

char traffic_status = 'a'; //статус по умолчанию - автоматическое управление
long int blink_start;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN1, OUTPUT); 
  pinMode(LED_PIN2, OUTPUT); 
  pinMode(LED_PIN3, OUTPUT); 
}

void update_state(){
	return;
}

void process_state(){
  //горит зелёный 10 секунд
  digitalWrite(LED_PIN1, HIGH);// включаем светодиод
  delay(10000);                // ждем 10 секунд
  digitalWrite(LED_PIN1, LOW); // выключаем светодиод
  
  //мигает зелёный 2 секунды
  
  //горит жёлтый (синий) 1 секунду
  digitalWrite(LED_PIN2, HIGH); 
  delay(1000);                   // ждем 1 секунду
  digitalWrite(LED_PIN2, LOW);     

  //горит красный 7 секунд
  digitalWrite(LED_PIN3, HIGH); 
  delay(7000);                   // ждем 7 секунд
  digitalWrite(LED_PIN3, LOW); 

  //горит жёлтый 1 секунду
  digitalWrite(LED_PIN2, HIGH); 
  delay(1000);                   // ждем 1 секунду
  digitalWrite(LED_PIN2, LOW);
  return;
}

void loop() {
  update_state();
  process_state();  
}
