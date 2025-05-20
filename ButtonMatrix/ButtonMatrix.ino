#define NROWS 3
#define NCOLS 3
#define SCAN_INTERVAL 10


const int rowPins[NROWS] = {2, 3, 4};

const int colPins[NCOLS] = {5, 6, 7};


bool buttonState[NROWS][NCOLS] = {0};
bool lastButtonState[NROWS][NCOLS] = {0};
unsigned long startTime[NROWS][NCOLS] = {0};
unsigned long duration[NROWS][NCOLS] = {0};

volatile int currentRow = 0;


void setupTimer() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15624;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}


ISR(TIMER1_COMPA_vect) {
  currentRow = (currentRow + 1) % NROWS;
}

void setup() {
  Serial.begin(9600);
  
  
  for (int i = 0; i < NROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  
  
  for (int i = 0; i < NCOLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
  
  setupTimer();
}

void updateButtonState() {
  
  PORTD &= ~(1 << rowPins[currentRow]); 
  
  
  for (int col = 0; col < NCOLS; col++) {
    bool state = !(PIND & (1 << colPins[col])); 
    buttonState[currentRow][col] = state;
    
    
    if (state && !lastButtonState[currentRow][col]) {
      startTime[currentRow][col] = millis();
    }
    
    else if (!state && lastButtonState[currentRow][col]) {
      duration[currentRow][col] = millis() - startTime[currentRow][col];
      Serial.print("Button ");
      Serial.print(currentRow * NCOLS + col + 1);
      Serial.print(" released: Duration = ");
      Serial.print(duration[currentRow][col]);
      Serial.print(" ms, Start time = ");
      Serial.print(startTime[currentRow][col]);
      Serial.println(" ms");
    }
    lastButtonState[currentRow][col] = state;
  }
  
  
  PORTD |= (1 << rowPins[currentRow]);
}

void printButtonChanges() {
  static bool lastPrintedState[NROWS][NCOLS] = {0};
  bool changed = false;
  
  
  for (int row = 0; row < NROWS; row++) {
    for (int col = 0; col < NCOLS; col++) {
      if (buttonState[row][col] != lastPrintedState[row][col]) {
        changed = true;
        lastPrintedState[row][col] = buttonState[row][col];
      }
    }
  }
  
  if (changed) {
    Serial.print("Pressed buttons: ");
    bool first = true;
    for (int row = 0; row < NROWS; row++) {
      for (int col = 0; col < NCOLS; col++) {
        if (buttonState[row][col]) {
          if (!first) Serial.print(", ");
          Serial.print(row * NCOLS + col + 1);
          first = false;
        }
      }
    }
    if (first) Serial.print("None");
    Serial.println();
  }
}

void loop() {
  updateButtonState(); 
  printButtonChanges();
}