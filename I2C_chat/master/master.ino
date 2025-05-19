#include <Wire.h>
struct Adress {
  String name;
  int address;
};



// Объявляем массив словаря
Adress tab_name[] = {
  {"Pasha", 9},
  {"Dasha", 10},
  {"Petya", 11}/*
  {"Adress-name", addres_number}
  */
};



const int size = sizeof(tab_name) / sizeof(tab_name[0]);
String name = "";
String message = "";

void setup() {
  Serial.begin(9600);
  Wire.begin(); // В качестве мастера, нет собственного адреса
}

void loop() {
  // Отправляем сообщения слейвам
  
  sendMessageToSlave(9);
  sendMessageToSlave(10);
  sendMessageToSlave(11);

  delay(2000); // интервал между циклами
}

void sendMessageToSlave(uint8_t address) {
  // Отправляем команду, чтобы слейв подготовил ответ
  Wire.beginTransmission(address);
  Wire.write("Request");  // Можно смотать любой сигнал, но лучше использовать протокол
  Wire.endTransmission();

  // Запрашиваем длину сообщения
  uint8_t len = requestMessageLength(address);

  if (len > 0) {
    // Запрашиваем сообщение
    String msg = requestMessage(address, len);
    Serial.print("Сообщение от слейва "); Serial.println(address); // От кого получено сообщение
    Serial.println(msg);
    // парсим сообщение
      int parsedAddress = parseMessage(msg); //куда надо отправить сообщение
      if (parsedAddress != -1) {
        Serial.println(parsedAddress);
        String replyMsg = "От " + getNameByAddress(address) + ": " + message;
        // Отправляем ответ по адресу
        
        Wire.beginTransmission(parsedAddress);
        Wire.write(replyMsg.c_str());
        Wire.endTransmission();
      }
      
  } else {
    Serial.print("Нет сообщения от слейва "); Serial.println(address);
  }
  delay(1000);
}

uint8_t requestMessageLength(uint8_t address) {
  uint8_t length = 0;
  Wire.requestFrom(address, 1); // запрашиваем 1 байт
  if (Wire.available()) {
    length = Wire.read();
  }
  return length;
}

String requestMessage(uint8_t address, uint8_t length) {
  String result = "";
  Wire.requestFrom(address, length);
  while (Wire.available()) {
    char c = Wire.read();
    result += c;
  }
  return result;
}

int parseMessage(const String& input) {
  int spaceIndex = input.indexOf('@');
  if (spaceIndex == -1) {
    name = input;
    message = "";
  } else {
    name = input.substring(0, spaceIndex);
    message = input.substring(spaceIndex + 1);
  }
  for (int i = 0; i < size; i++) {
    if (tab_name[i].name == name) {
      return tab_name[i].address;
    }
  }
  return -1;
}

String getNameByAddress(int address) {
  for (int i = 0; i < sizeof(tab_name)/sizeof(tab_name[0]); i++) {
    if (tab_name[i].address == address) {
      return tab_name[i].name;
    }
  }
  return "Неизвестно";
}