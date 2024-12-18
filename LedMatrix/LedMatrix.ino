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
1,4 = ! // combine(1\4)
2,3 = @ // combine(2\3)
1,2,4 = # // combine(1,2\4)
2,3,4 = $ // combine(2,4\3)
3,4,1 = % // combine(3,4\1)
1,3,2 = ^ // combine(1,3\2)

*/


#define FIRST_PIN 3
#define SECOND_PIN 4
#define THIRD_PIN 5
#define FOURTH_PIN 6

int state=0;
int previous_state=state;
uint32_t blink_start=0;
int current=1;
int previous_current=current;

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
      case '!': //1,4
        previous_state=state;
        state=10;
        break;
      case '@': //2,3
        previous_state=state;
        state=11;
        break;
      case '#': //1,2,4
        previous_state=state;
        state=12;
        break;
      case '$': //2,3,4
        previous_state=state;
        state=13;
        break;
      case '%': //3,4,1
        previous_state=state;
        state=14;
        break;
      case '^': //1,3,2
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
      if (previous_state!=10){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=10;
      } else{
        switch(current){
          case 1:
            if (previous_current!=1){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=1;
              blink_start=millis();
            } else {
              
              
              analogWrite(FIRST_PIN,255);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,255);
            }
            if(millis()-blink_start>=1){
              current=2;
            }
            break;
          case 2:
            if (previous_current!=2){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=2;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,255);
              analogWrite(THIRD_PIN,255);
              analogWrite(FOURTH_PIN,0);
              
            }
            if(millis()-blink_start>=1){
              current=1;
            }
            break;
          default:
            break;
        }        
        /*1,4 = ! // combine(1\4)*/
      }   
      break;
    case 11: //2,3
      if (previous_state!=11){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=11;
      } else{
        /*2,3 = @ // combine(2\3)*/
        switch(current){
          case 1:
            if (previous_current!=1){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=1;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,255);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,255);
              analogWrite(FOURTH_PIN,0);
            }
            if(millis()-blink_start>=1){
              current=2;
            }
            break;
          case 2:
            if (previous_current!=2){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=2;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,255);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,255);
              
            }
            if(millis()-blink_start>=1){
              current=1;
            }
            break;
          default:
            break;
        }   
      }   
      break;
    case 12: //1,2,4
      if (previous_state!=12){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=12;
      } else{
        /*1,2,4 = # // combine(1,2\4)*/
        switch(current){
          case 1:
            if (previous_current!=1){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=1;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,255);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
            }
            if(millis()-blink_start>=1){
              current=2;
            }
            break;
          case 2:
            if (previous_current!=2){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=2;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,255);
              analogWrite(THIRD_PIN,255);
              analogWrite(FOURTH_PIN,0);
              
            }
            if(millis()-blink_start>=1){
              current=1;
            }
            break;
          default:
            break;
        }  
      }   
      break;
    case 13: //2,3,4
      if (previous_state!=13){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=13;
      } else{
        /*1,4 = ! //2,3,4 = $ // combine(2,4\3)*/
        switch(current){
          case 1:
            if (previous_current!=1){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=1;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,255);
              analogWrite(SECOND_PIN,255);
              analogWrite(THIRD_PIN,255);
              analogWrite(FOURTH_PIN,0);
            }
            if(millis()-blink_start>=1){
              current=2;
            }
            break;
          case 2:
            if (previous_current!=2){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=2;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,255);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,255);
              
            }
            if(millis()-blink_start>=1){
              current=1;
            }
            break;
          default:
            break;
        }  
      }  
      break;
    case 14: //3,4,1
      if (previous_state!=14){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=14;
      } else{
        /*3,4,1 = % // combine(3,4\1)*/
        switch(current){
          case 1:
            if (previous_current!=1){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=1;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,255);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
            }
            if(millis()-blink_start>=1){
              current=2;
            }
            break;
          case 2:
            if (previous_current!=2){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=2;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,255);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,255);
              
            }
            if(millis()-blink_start>=1){
              current=1;
            }
            break;
          default:
            break;
        }  
      }  
      break;
    case 15: //1,3,2
      if (previous_state!=15){
        analogWrite(FIRST_PIN,0);
        analogWrite(SECOND_PIN,0);
        analogWrite(THIRD_PIN,0);
        analogWrite(FOURTH_PIN,0);
        previous_state=15;
      } else{
        /*1,3,2 = ^ // combine(1,3\2)*/
        switch(current){
          case 1:
            if (previous_current!=1){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=1;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,255);
              analogWrite(SECOND_PIN,255);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,255);
            }
            if(millis()-blink_start>=1){
              current=2;
            }
            break;
          case 2:
            if (previous_current!=2){
              analogWrite(FIRST_PIN,0);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,0);
              analogWrite(FOURTH_PIN,0);
              previous_current=2;
              blink_start=millis();
            } else {
              analogWrite(FIRST_PIN,255);
              analogWrite(SECOND_PIN,0);
              analogWrite(THIRD_PIN,255);
              analogWrite(FOURTH_PIN,0);
              
            }
            if(millis()-blink_start>=1){
              current=1;
            }
            break;
          default:
            break;
        }  
      }  
      break;
    default:
      break;
  }
}

void loop() {
  update_state();
  process_state();
}
