#define BUTTON_PIN 2 
#define PRESSED HIGH
#define DEBOUNCE_INTERVALS 10

volatile bool report_to_user = false;
volatile int count_stable_readings = 0;
volatile bool button_state = false;
volatile bool last_status_button = false;
bool actual_status_button = LOW;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1A |= (1 << WGM12);
  OCR1A = 1249;
  TCCR1B |= (1 << WGM12); // делитель 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

ISR(TIMER1_COMPA_vect) {
  actual_status_button = digitalRead(BUTTON_PIN);
  if (actual_status_button == last_status_button) {
    if (count_stable_readings < DEBOUNCE_INTERVALS) {
      count_stable_readings++;
    }
  } else {
    count_stable_readings = 0;
    last_status_button = actual_status_button;
  }
  if (count_stable_readings >= DEBOUNCE_INTERVALS) {
    if (actual_status_button
 != button_state) {
      button_state = actual_status_button;
      report_to_user = true;
    }
  }
}

void loop() {
  if (report_to_user) {
    if (button_state == PRESSED) {
      Serial.println("Button pressed");
    } else {
      Serial.println("Button released");
    }
    report_to_user = false;
  }
}