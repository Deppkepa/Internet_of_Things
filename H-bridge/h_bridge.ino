const int IN1 = 2;
const int IN2 = 3;
const int ENA = 9;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  Serial.begin(9600);
}


// direction — "forward", "backward", "stop"
// speed — 0-255
void controlMotor(String direction, int speed) {
  if (direction == "forward") {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (direction == "backward") {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else { // остановка
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  analogWrite(ENA, speed);
}

void loop() {
  // Вперед с низкой скоростью
  controlMotor("forward", 20);
  Serial.println("forward");
  
  delay(10000);
  // Назад на высокой скорости
  controlMotor("backward", 255);
  Serial.println("backward");
  delay(10000);
  
  // Остановка
  controlMotor("stop", 0);
  Serial.println("stop");
  delay(10000);
}
