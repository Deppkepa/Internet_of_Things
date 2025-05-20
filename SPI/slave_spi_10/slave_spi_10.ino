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
  Serial.println("Nano Slave Ready");
}

ISR(SPI_STC_vect) {
  receivedData = SPDR; // Читаем данные из регистра SPI

  // Обрабатываем команду и готовим ответ
  if (receivedData == 0x01) {
    responseData = 42; // Пример статуса для Nano (например, "все OK, значение 42")
  } else if (receivedData == 0x02) {
    responseData = 10; // Пример версии для Nano (например, версия 1.0)
  } else {
    responseData = 0xFF; // Неизвестная команда
  }

  SPDR = responseData; // Отправляем ответ мастеру
  dataReceived = true;
}

void loop() {
  if (dataReceived) {
    Serial.print("Nano received command: ");
    Serial.print(receivedData, HEX);
    Serial.print(" | Sent response: ");
    Serial.println(responseData, DEC);
    dataReceived = false;
  }
}