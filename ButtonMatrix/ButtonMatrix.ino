#define RON_2 2
#define RON_3 3
#define RON_4 4

#define COL_5 5
#define COL_6 6
#define COL_7 7 

void setup()
{
  pinMode(RON_2, OUTPUT);
  pinMode(RON_3, OUTPUT);
  pinMode(RON_4, OUTPUT);
  
  pinMode(COL_5, INPUT_PULLUP);
  pinMode(COL_6, INPUT_PULLUP);
  pinMode(COL_7, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(RON_2, LOW);
  digitalWrite(RON_3, HIGH);
  digitalWrite(RON_4, HIGH);
  
  bool btn1_state = digitalRead(COL_5);
  bool btn2_state = digitalRead(COL_6);
  bool btn3_state = digitalRead(COL_7);
  if (btn1_state == false) {
  	Serial.println("Buttom 1 presed");
  }
  if (btn2_state == false) {
  	Serial.println("Buttom 2 presed");
  }
  if (btn3_state == false) {
  	Serial.println("Buttom 3 presed");
  }
  delay(50);
}