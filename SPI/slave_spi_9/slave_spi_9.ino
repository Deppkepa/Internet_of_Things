#include <SPI.h>

volatile byte receivedData = 0;
volatile bool dataReceived = false;
byte responseData = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Ждем подключения Serial Monitor
  }

  // Настройка SPI как слейв
  pinMode(MISO, OUTPUT); // Устанавливаем MISO как выход
  SPCR |= _BV(SPE); // Включаем SPI в режиме слейва
  SPI.attachInterrupt(); // Включаем прерывания для SPI
  Serial.println("Uno Slave Ready");
}

ISR(SPI_STC_vect) {
  receivedData = SPDR; // Читаем данные из регистра SPI

  // Обрабатываем команду и готовим ответ
  if (receivedData == 0x01) {
    responseData = 75; // Пример статуса для Uno (например, "все OK, значение 75")
  } else if (receivedData == 0x02) {
    responseData = 20; // Пример версии для Uno (например, версия 2.0)
  } else {
    responseData = 0xFF; // Неизвестная команда
  }

  SPDR = responseData; // Отправляем ответ мастеру
  dataReceived = true;
}

void loop() {
  if (dataReceived) {
    Serial.print("Uno received command: ");
    Serial.print(receivedData, HEX);
    Serial.print(" | Sent response: ");
    Serial.println(responseData, DEC);
    dataReceived = false;
  }
}