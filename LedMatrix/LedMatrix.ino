/*
off = 0 // 0 0 0 0
on = 1 // 1 1 0 0
1 = 2 // 1 0 0 1
2 = 3 // 1 0 1 0
3 = 4 // 0 1 0 1
4 = 5 // 0 1 1 0
1,2 = 6 // 1 0 0 0
2,4 = 7 // 1 1 1 0
3,4 = 8 // 0 1 0 0
1,3 = 9 // 1 1 0 1
1,4 = 10 // combine(1\4)
2,3 = 11 // combine(2\3)
1,2,4 = 12 // combine(1,2\4)
2,3,4 = 13 // combine(2,4\3)
3,4,1 = 14 // combine(3,4\1)
1,3,2 = 15 // combine(1,3\2)

*/


#define FIRST_PIN 3
#define SECOND_PIN 4
#define THIRD_PIN 5
#define FOURTH_PIN 6

int state=0;
int previous_state=state;

void setup() {
  Serial.begin(9600);
  pinMode(FIRST_PIN, OUTPUT);
  pinMode(SECOND_PIN, OUTPUT);
  pinMode(THIRD_PIN, OUTPUT);
  pinMode(FOURTH_PIN, OUTPUT);
}

void update_state(){
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    switch(cmd){
      case '0': //off
        previous_state=state;
        state=0;
        break;
      case '1': //on
        previous_state=state;
        state=1;
        break;
      case '2': //1
        previous_state=state;
        state=2;
        break;
      case '3': //2
        previous_state=state;
        state=3;
        break;
      case '4': //3
        previous_state=state;
        state=4;
        break;
      case '5': //4
        previous_state=state;
        state=5;
        break;
      case '6': //1,2
        previous_state=state;
        state=6;
        break;
      case '7': //2,4
        previous_state=state;
        state=7;
        break;
      case '8': //3,4
        previous_state=state;
        state=8;
        break;
      case '9': //1,3
        previous_state=state;
        state=9;
        break;
      case '10': //1,4
        previous_state=state;
        state=10;
        break;
      case '11': //2,3
        previous_state=state;
        state=11;
        break;
      case '12': //1,2,4
        previous_state=state;
        state=12;
        break;
      case '13': //2,3,4
        previous_state=state;
        state=13;
        break;
      case '14': //3,4,1
        previous_state=state;
        state=14;
        break;
      case '15': //1,3,2
        previous_state=state;
        state=15;
        break;
      default: //неправильная комманда
        previous_state=state;
        state=0;
        break;
    }
  }
}

void process_state(){
  switch(state){
    case 0: //off
      analogWrite(FIRST_PIN,0);
      analogWrite(SECOND_PIN,0);
      analogWrite(THIRD_PIN,0);
      analogWrite(FOURTH_PIN,0);
    case 1: //on
      if (previous_state!=1){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=1;
      } else{
        analogWrite(FIRST_PIN,255);
        analogWrite(SECOND_PIN,255);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
      }      
      break;
    case 2: //1
      if (previous_state!=2){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=2;
      } else{
        analogWrite(FIRST_PIN,255);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,255);
      }   
      break;
    case 3: //2
      if (previous_state!=3){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=3;
      } else{
        analogWrite(FIRST_PIN,255);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,255);
        analogWrite(FOURTH_PIN,0);
      }   
      break;
    case 4: //3
      if (previous_state!=4){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=4;
      } else{
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,255);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,255);
      } 
      break;
    case 5: //4
      if (previous_state!=5){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=5;
      } else{
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,255);
        analogWrite(THIRD_PIN,255);
        analogWrite(FOURTH_PIN,0);
      } 
      break;
    case 6: //1,2
      if (previous_state!=6){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=6;
      } else{
        analogWrite(FIRST_PIN,255);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
      } 
      break;
    case 7: //2,4
      if (previous_state!=7){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=7;
      } else{
        analogWrite(FIRST_PIN,255);
        analogWrite(SECOND_PIN,255);
        analogWrite(THIRD_PIN,255);
        analogWrite(FOURTH_PIN,0);
      } 
      break;
    case 8: //3,4
      if (previous_state!=8){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=8;
      } else{
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,255);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
      } 
      break;
    case 9: //1,3
      if (previous_state!=9){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=9;
      } else{
        analogWrite(FIRST_PIN,255);
        analogWrite(SECOND_PIN,255);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,255);
      } 
      break;
    case 10: //1,4
      break;
    case 11: //2,3
      break;
    case 12: //1,2,4
      break;
    case 13: //2,3,4
      break;
    case 14: //3,4,1
      break;
    case 15: //1,3,2
      break;
    default:
      break;
  }
}

void loop() {
  update_state();
  process_state();
}
