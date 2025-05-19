#include <Wire.h>
String userMessage = "";
bool sendLength = true;

void setup(){
  Serial.begin(9600);
  Wire.begin(10);                
  Wire.onReceive(receiveEvent); 
  Wire.onRequest(requestEvent);
  Serial.println("Slave готов");
}

void loop(){
    if (Serial.available()) {
    
    userMessage = readSerialMessage();
    Serial.print("Новое сообщение: ");
    Serial.println(userMessage);
    }

  // В основном цикле ничего дополнительно делать не нужно
  delay(100);

}


void receiveEvent(int howMany) {
  String receivedStr = "";
  for (int i=0; i<howMany; i++) {
    if (Wire.available()) {
      char c = Wire.read();
      receivedStr += c;
    }
  }
  Serial.print("Получено сообщение: ");
  Serial.println(receivedStr);
}


void requestEvent() {
  if (userMessage.length() != 0 ){
    
    if (sendLength) {
      // Отправляем длину сообщения
      uint8_t len = userMessage.length();
      
      Wire.write(len);
      // Устанавливаем флаг, чтобы при следующем запросе отправить сообщение
      sendLength = false;
      Serial.print("Отправленная длина: ");
      Serial.println(len);
    } else {
      // Отправляем сообщение
      Wire.write(userMessage.c_str());
      // после этого снова будем отправлять длину при следующем запросе
      Serial.print("Отправленное сообщение: ");
      Serial.println(userMessage);
      sendLength = true;
      userMessage = "";
    }
  }
}

// Функция чтения сообщения из Serial
String readSerialMessage() {
  String message = "";
  // Ждем, пока пользователь не введет сообщение
  while (Serial.available() == 0) {
    delay(10);
  }
  // Читаем все доступные символы
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') {
      break;
    }
    message += c;
    delay(10);
  }
  return message;
}