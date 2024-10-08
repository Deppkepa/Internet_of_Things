#define RED_PIN 10
#define YELLOW_PIN 12
#define GREEN_PIN 13

#define GREEN_TIME 10000
#define RED_TIME 7000
#define YELLOW_TIME 1000
#define BLINK_GREEN_TIME 2000
#define INTERVAL 200

enum State { RED, YELLOW, GREEN, BLINK_GREEN }; // Состояния светофора
State start_color = GREEN; // Начальное состояние
State memory = GREEN;
unsigned long end_time = 0;
int count = 0;
uint32_t start_blink_time, end_blink_time = 0;
bool led_stat = true;

void setup() {
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void avto_traffic_lights() {
  unsigned long start_time = millis();
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
        if (start_time - end_time >= GREEN_TIME) {
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
  avto_traffic_lights();
}
