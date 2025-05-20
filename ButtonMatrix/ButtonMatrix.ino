#define NROWS 3
#define NCOLS 3
#define SCAN_INTERVAL 1 

const int rowPins[NROWS] = {2, 3, 4};

const int colPins[NCOLS] = {5, 6, 7};


bool buttonState[NROWS][NCOLS] = {0};
bool lastButtonState[NROWS][NCOLS] = {0};
unsigned long startTime[NROWS][NCOLS] = {0};
unsigned long duration[NROWS][NCOLS] = {0};

volatile int currentRow = 0;
volatile bool isScanning = true;
unsigned long lastScanTime = 0;
const int MAIN_DELAY = 50;


void setupTimer() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 62; 
  TCCR1B |= (1 << WGM12); 
  TCCR1B |= (1 << CS12); 
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}


ISR(TIMER1_COMPA_vect) {
  if (!isScanning && millis() > lastScanTime + MAIN_DELAY) {
    isScanning = true;
  }

  if (isScanning) {
    updateButtonState(); 
    currentRow = (currentRow + 1) % NROWS; 
  }

  if (currentRow == 0 && isScanning) {
    isScanning = false; 
    lastScanTime = millis();
    printButtonChanges(); 
  }
}

void setup() {
  Serial.begin(9600);
  
  
  DDRD |= (1 << rowPins[0]) | (1 << rowPins[1]) | (1 << rowPins[2]);
  PORTD |= (1 << rowPins[0]) | (1 << rowPins[1]) | (1 << rowPins[2]); 
  
  
  DDRD &= ~((1 << colPins[0]) | (1 << colPins[1]) | (1 << colPins[2]));
  PORTD |= (1 << colPins[0]) | (1 << colPins[1]) | (1 << colPins[2]); 
  
  setupTimer(); 
}

void updateButtonState() {
  
  PORTD |= (1 << rowPins[0]) | (1 << rowPins[1]) | (1 << rowPins[2]);
  
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
  
}