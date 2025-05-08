#define BUTTON_PIN 2
#define BOUNCE_TIME 5
#define TIMER_INTERVAL_TICK 10
#define BUTTON_PRESSED HIGH

volatile bool button_stable_state = false; // хранит статус последнего стабильного состояния кнопки 
volatile bool report_to_user = false; // Флаг для передачи сообщения в серийную консоль
volatile int check_count = 0; // Счетчик для 10 проверок (5 мс)
volatile bool last_button_state = 0; // последнее состояние кнопки
bool current_state = 0; // текущее состояние кнопки
int count_click_button = 0; // колличество нажатий на кнопку (подтвержденных)

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
  noInterrupts(); // отключение всех прерываний для настройки таймера
  // обнуление регистров
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR2A |= (1 << WGM21); // настойка на режим CTC (Clear Timer on Compare Match)
  OCR2A = 77;
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // пределитель 1024
  TIMSK2 |= (1 << OCIE2A); // включение прерывание по совпадению с регистром OCR2A
  interrupts(); // включение глобальных прерываний
}

void loop() {
  if(report_to_user) {
    Serial.print("Press candidate: ");
    Serial.println(count_click_button);
    report_to_user = false;
  }
}

ISR(TIMER2_COMPA_vect) {
  current_state = digitalRead(BUTTON_PIN);
  if(current_state == last_button_state) {  
    if(check_count < TIMER_INTERVAL_TICK) {
      check_count++;
    } else {
      if(current_state != button_stable_state) {
        button_stable_state = current_state;
        if(button_stable_state == BUTTON_PRESSED) {
          report_to_user = true;
          count_click_button++;
        }
      }
    }
  } else {
    last_button_state = current_state;
    check_count = 0;
  }
}

