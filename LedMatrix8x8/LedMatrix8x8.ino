#define PIN_1 A0 // столбец 4
#define PIN_2 A1 //  столбец 2
#define PIN_3 A2 // ряд 7  
#define PIN_4 A3 // ряд 6
#define PIN_5 13 //  столбец 1
#define PIN_6 12 //  столбец 3
#define PIN_7 11 // ряд 4
#define PIN_8 10 // столбец 6
#define PIN_9 9 //  ряд 1
#define PIN_10 8 //  ряд 2
#define PIN_11 7 // столбец 7
#define PIN_12 6 //  ряд 8
#define PIN_13 5 // столбец 5
#define PIN_14 4 // ряд 3
#define PIN_15 3 // ряд 5
#define PIN_16 2 // столбец 8 

void setup() {
  Serial.begin(9600);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
  pinMode(PIN_5, OUTPUT);
  pinMode(PIN_6, OUTPUT);
  pinMode(PIN_7, OUTPUT);
  pinMode(PIN_8, OUTPUT);
  pinMode(PIN_9, OUTPUT);
  pinMode(PIN_10, OUTPUT);
  pinMode(PIN_11, OUTPUT);
  pinMode(PIN_12, OUTPUT);
  pinMode(PIN_13, OUTPUT);
  pinMode(PIN_14, OUTPUT);
  pinMode(PIN_15, OUTPUT);
  pinMode(PIN_16, OUTPUT);

}

void draw(int m[8][8]){
  for (int i =0; i<8; i++){
    digitalWrite(PIN_5,LOW); //столбец 1
    digitalWrite(PIN_2,LOW); //столбец 2
    digitalWrite(PIN_6,LOW); //столбец 3
    digitalWrite(PIN_1,LOW); //столбец 4
    digitalWrite(PIN_13,LOW); //столбец 5
    digitalWrite(PIN_8,LOW); //столбец 6
    digitalWrite(PIN_11,LOW); //столбец 7
    digitalWrite(PIN_16,LOW); //столбец 8
    
    switch (i) {
      case 0: 
        digitalWrite(PIN_9, HIGH);
        digitalWrite(PIN_10, LOW);
        digitalWrite(PIN_14, LOW);
        digitalWrite(PIN_15, LOW);
        digitalWrite(PIN_7, LOW);
        digitalWrite(PIN_4, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_12, LOW);
        break;
      case 1:
        digitalWrite(PIN_9, LOW);
        digitalWrite(PIN_10, HIGH);
        digitalWrite(PIN_14, LOW);
        digitalWrite(PIN_15, LOW);
        digitalWrite(PIN_7, LOW);
        digitalWrite(PIN_4, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_12, LOW);
        break;
      case 2:
        digitalWrite(PIN_9, LOW);
        digitalWrite(PIN_10, LOW);
        digitalWrite(PIN_14, HIGH);
        digitalWrite(PIN_15, LOW);
        digitalWrite(PIN_7, LOW);
        digitalWrite(PIN_4, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_12, LOW);
        break;
      case 3:
        digitalWrite(PIN_9, LOW);
        digitalWrite(PIN_10, LOW);
        digitalWrite(PIN_14, LOW);
        digitalWrite(PIN_15, HIGH);
        digitalWrite(PIN_7, LOW);
        digitalWrite(PIN_4, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_12, LOW);
        break; 
      case 4:
        digitalWrite(PIN_9, LOW);
        digitalWrite(PIN_10, LOW);
        digitalWrite(PIN_14, LOW);
        digitalWrite(PIN_15, LOW);
        digitalWrite(PIN_7, HIGH);
        digitalWrite(PIN_4, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_12, LOW);      
        break;
      case 5:
        digitalWrite(PIN_9, LOW);
        digitalWrite(PIN_10, LOW);
        digitalWrite(PIN_14, LOW);
        digitalWrite(PIN_15, LOW);
        digitalWrite(PIN_7, LOW);
        digitalWrite(PIN_4, HIGH);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_12, LOW);
        break;
      case 6:
        digitalWrite(PIN_9, LOW);
        digitalWrite(PIN_10, LOW);
        digitalWrite(PIN_14, LOW);
        digitalWrite(PIN_15, LOW);
        digitalWrite(PIN_7, LOW);
        digitalWrite(PIN_4, LOW);
        digitalWrite(PIN_3, HIGH);
        digitalWrite(PIN_12, LOW);
        break;
      case 7:
        digitalWrite(PIN_9, LOW);
        digitalWrite(PIN_10, LOW);
        digitalWrite(PIN_14, LOW);
        digitalWrite(PIN_15, LOW);
        digitalWrite(PIN_7, LOW);
        digitalWrite(PIN_4, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_12, HIGH);
        break;
    }
    
    digitalWrite(PIN_5,!m[i][0]); //столбец 1
    digitalWrite(PIN_2,!m[i][1]); //столбец 2
    digitalWrite(PIN_6,!m[i][2]); //столбец 3
    digitalWrite(PIN_1,!m[i][3]); //столбец 4
    digitalWrite(PIN_13,!m[i][4]); //столбец 5
    digitalWrite(PIN_8,!m[i][5]); //столбец 6
    digitalWrite(PIN_11,!m[i][6]); //столбец 7
    digitalWrite(PIN_16,!m[i][7]); //столбец 8 
    delay(1);
    
  }
}

void loop() {

  /* 
    1 2 3 4 5 6 7 8
  1 0 0 0 0 0 0 0 0
  2 0 1 0 0 0 0 1 0
  3 1 1 1 0 0 1 1 1
  4 1 1 1 1 1 1 1 1
  5 1 1 1 1 1 1 1 1
  6 0 1 1 1 1 1 1 0
  7 0 0 1 1 1 1 0 0
  8 0 0 0 1 1 0 0 0


  */
  int m[][8]={
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0}
    };
  draw(m); 
}
