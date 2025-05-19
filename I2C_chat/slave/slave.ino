#include <Wire.h>

String userMessage = "";
bool sendLength = true;

void setup() {
  Serial.begin(9600);
  Wire.begin(9);  // укажите ваш адрес слейва
  Wire.onReceive(receiveEvent);   // регистрируем обработчик для входящих данных
  Wire.onRequest(requestEvent);   // регистрируем обработчик для запроса данных
  Serial.println("Slave готов");
}

void loop() {
  if (Serial.available()) {
    
    userMessage = readSerialMessage();
    Serial.print("Новое сообщение: ");
    Serial.println(userMessage);
  }
  // В основном цикле ничего дополнительно делать не нужно
  delay(100);
}

// Обработчик приема данных от мастера
void receiveEvent(int howMany) {
  String receivedStr = "";
  while (Wire.available()) {
    char c = Wire.read();
    receivedStr += c;  // собираем сообщение
  }
  Serial.print("Получено сообщение: ");
  Serial.println(receivedStr);
  // Можно обновить userMessage, если нужно
  //userMessage = receivedStr;
}

// Обработчик запроса от мастера — отправляем длину userMessage
void requestEvent() {
  if (userMessage.length() != 0 ){
    if (sendLength) {
      // Отправляем длину сообщения
      uint8_t len = userMessage.length();
      Serial.println(len);
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
