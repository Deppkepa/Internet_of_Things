#include <SPI.h>

// Пины для CS (Chip Select) для каждого слейва
#define CS_NANO PA4
#define CS_UNO 10

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Ждем подключения Serial Monitor
  }

  // Настройка пинов CS как выходов
  pinMode(CS_NANO, OUTPUT);
  pinMode(CS_UNO, OUTPUT);
  digitalWrite(CS_NANO, HIGH); // Отключаем слейвы на старте
  digitalWrite(CS_UNO, HIGH);

  // Инициализация SPI как мастер
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16); // Устанавливаем скорость
  Serial.println("Master STM32 Ready");
}

void loop() {
  byte response;

  // Запрос статуса у Nano (команда 0x01)
  Serial.println("Sending STATUS request to Nano...");
  digitalWrite(CS_NANO, LOW); // Активируем Nano
  response = SPI.transfer(0x01); // Отправляем команду запроса статуса
  digitalWrite(CS_NANO, HIGH); // Деактивируем Nano
  Serial.print("Nano STATUS response: ");
  Serial.println(response, DEC);

  delay(500);

  // Запрос версии у Nano (команда 0x02)
  Serial.println("Sending VERSION request to Nano...");
  digitalWrite(CS_NANO, LOW); // Активируем Nano
  response = SPI.transfer(0x02); // Отправляем команду запроса версии
  digitalWrite(CS_NANO, HIGH); // Деактивируем Nano
  Serial.print("Nano VERSION response: ");
  Serial.println(response, DEC);

  delay(500);

  // Запрос статуса у Uno (команда 0x01)
  Serial.println("Sending STATUS request to Uno...");
  digitalWrite(CS_UNO, LOW); // Активируем Uno
  response = SPI.transfer(0x01); // Отправляем команду запроса статуса
  digitalWrite(CS_UNO, HIGH); // Деактивируем Uno
  Serial.print("Uno STATUS response: ");
  Serial.println(response, DEC);

  delay(500);

  // Запрос версии у Uno (команда 0x02)
  Serial.println("Sending VERSION request to Uno...");
  digitalWrite(CS_UNO, LOW); // Активируем Uno
  response = SPI.transfer(0x02); // Отправляем команду запроса версии
  digitalWrite(CS_UNO, HIGH); // Деактивируем Uno
  Serial.print("Uno VERSION response: ");
  Serial.println(response, DEC);

  delay(2000); // Задержка перед следующим циклом
}