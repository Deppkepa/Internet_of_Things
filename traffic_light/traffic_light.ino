#define LED_PIN1 13 //Зелёный
#define LED_PIN2 12 //Жёлтый (синий)
#define LED_PIN3 10 //Красный

#define COMMAND_MANUAL 'm' //команда на ручное управление
#define COMMAND_AUTO 'a' //команда на автоматическое управление

#define TRAFFIC_AUTO 0
#define TRAFFIC_MANUAL 1

#define LED_RED 'r' //метка красного светодиода
#define LED_GREEN 'g' //метка зелёного светодиода
#define LED_YELLOW 'y' //метка жёлтого(синего) светодиода

#define STATE_LED_RED 0
#define STATE_LED_GREEN 1
#define STATE_LED_YELLOW 2

#define MANUAL_INTERVAL 60

#define GREEN_USUAL_INTERVAL 10000
#define YELLOW_USUAL_INTERVAL 1000
#define YELLOW_UNCOMMON_INTERVAL 3000
#define RED_USUAL_INTERVAL 7000

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

int traffic_status=TRAFFIC_AUTO; //статус по умолчанию - автоматическое управление
long int blink_start;
char led;
long int manual_start, green_start, yellow_start, red_start, green_blink_start;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN1, OUTPUT); 
  pinMode(LED_PIN2, OUTPUT); 
  pinMode(LED_PIN3, OUTPUT); 
}

void update_state(){
	if (manual_start){
		if (millis() <= manual_start+MANUAL_INTERVAL){
			traffic_status=TRAFFIC_AUTO;
		}
	}
	if (Serial.available() > 0) {
		char cmd = Serial.read();
		if(cmd == COMMAND_AUTO){
			traffic_status=TRAFFIC_AUTO;
		}
		else if (cmd == COMMAND_MANUAL){
			manual_start=millis();
			traffic_status=TRAFFIC_MANUAL;
		}
		else if(cmd == LED_RED){
			if (traffic_status==TRAFFIC_MANUAL){
				led=STATE_LED_RED;
			} else{
				Serial.println("Cannot perform this command. - Auto mode");
			}
		}
		else if (cmd ==LED_GREEN){
			if (traffic_status==TRAFFIC_MANUAL){
				led=STATE_LED_GREEN;
			} else{
				Serial.println("Cannot perform this command. - Auto mode");
			}
		} else{
			Serial.println("Unknown command");
		}
	}
}


void process_state(){
	if (traffic_status==TRAFFIC_AUTO){
		//
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
	}
	else if (traffic_status==TRAFFIC_MANUAL){
		int k=0; 
	}

}

void loop() {
  update_state();
  process_state();  
}
