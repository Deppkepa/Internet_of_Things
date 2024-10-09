#define RED_PIN 10
#define YELLOW_PIN 12
#define GREEN_PIN 13

#define GREEN_TIME 10000
#define RED_TIME 7000
#define YELLOW_TIME 1000
#define BLINK_GREEN_TIME 2000
#define MANUAL_YELLOW_TIME 3000
#define INTERVAL 200
#define MANUAL_INTERVAL 60000

#define SET_TRAFFIC_MANUAL 'm'
#define SET_TRAFFIC_RED 'r'
#define SET_TRAFFIC_GREEN 'g'
#define SET_TRAFFIC_YELLOW 'y'

enum State { RED, YELLOW, GREEN, BLINK_GREEN }; // Состояния светофора
State start_color = GREEN; // Начальное состояние
State memory = GREEN;
unsigned long end_time = 0, manual_time = 0, start_time;
int count = 0;
uint32_t start_blink_time, end_blink_time = 0;
bool led_stat = true, traffic_auto=true;
char manual_color=SET_TRAFFIC_YELLOW;

void setup() {
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}
void manual_traffic_lights() {
	if (millis() - manual_time >= MANUAL_INTERVAL){
		traffic_auto=true;
    manual_color=SET_TRAFFIC_YELLOW;
		return;
	}
	if (Serial.available() > 0) {
		char cmd = Serial.read();
		
		if ((cmd == SET_TRAFFIC_GREEN || cmd == SET_TRAFFIC_RED) && cmd!=manual_color){
			manual_color=cmd;
    }
  }
	
	switch(manual_color){
		case SET_TRAFFIC_RED:
			if (start_color == RED){
        start_color=RED;
				digitalWrite(RED_PIN, HIGH);
				digitalWrite(YELLOW_PIN, LOW);
				digitalWrite(GREEN_PIN, LOW);
			}
			else {
				start_time=millis();
				if (start_time - end_time >= MANUAL_YELLOW_TIME) {
				  end_time = start_time;
				  start_color = RED;
				}
				digitalWrite(RED_PIN, LOW);
				digitalWrite(YELLOW_PIN, HIGH);
				digitalWrite(GREEN_PIN, LOW);
			}			
			break;
		case SET_TRAFFIC_GREEN:
			if (start_color == GREEN){
        start_color=GREEN;
				digitalWrite(RED_PIN, LOW);
				digitalWrite(YELLOW_PIN, LOW);
				digitalWrite(GREEN_PIN, HIGH);
			}
			else {
				start_time=millis();
				if (start_time - end_time >= MANUAL_YELLOW_TIME) {
				  end_time = start_time;
				  start_color = GREEN;
				}
				digitalWrite(RED_PIN, LOW);
				digitalWrite(YELLOW_PIN, HIGH);
				digitalWrite(GREEN_PIN, LOW);
			}			
			break;
		case SET_TRAFFIC_YELLOW:
			memory=start_color;
			start_color=YELLOW;
			digitalWrite(RED_PIN, LOW);
			digitalWrite(YELLOW_PIN, HIGH);
			digitalWrite(GREEN_PIN, LOW);
      break;
	}	
}


void avto_traffic_lights() {
  start_time = millis();
  switch (start_color) {
      case GREEN:
        if (start_time - end_time >= GREEN_TIME) {
          end_time = start_time;
          start_color = BLINK_GREEN;
          memory = GREEN;
        }
        digitalWrite(RED_PIN, LOW);
        digitalWrite(YELLOW_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
        break;

      case BLINK_GREEN: 
        if (start_time - end_time >= BLINK_GREEN_TIME) { 
            end_time = start_time; 
            start_color = YELLOW;
        } 
          start_blink_time = millis();
        if( ( start_blink_time - end_blink_time ) > INTERVAL || start_blink_time < end_blink_time ){
          end_blink_time = start_blink_time;      
          digitalWrite(13, led_stat); 
          led_stat = !led_stat;
        }
        break;

      case YELLOW:
        if (start_time - end_time >= YELLOW_TIME) {
          end_time = start_time;
          if (memory == GREEN) {
            start_color = RED;
          } else {
            start_color = GREEN;
          }
        }
        digitalWrite(RED_PIN, LOW);
        digitalWrite(YELLOW_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        break;

      case RED:
        if (start_time - end_time >= RED_TIME) {
          end_time = start_time;
          start_color = YELLOW;
          memory = RED;
        }
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(YELLOW_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        break;
  }
};


void loop() {
	if (Serial.available() > 0 && traffic_auto){
		char cmd = Serial.read();
		if (cmd == SET_TRAFFIC_MANUAL){
			manual_time = millis();
			traffic_auto=false;
      memory=start_color;
      start_color=YELLOW;
			manual_traffic_lights();
		} 
	} 
	else if (traffic_auto){
		avto_traffic_lights();
	}
	else {
		manual_traffic_lights();
	}
}
