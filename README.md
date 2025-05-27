# Internet_of_Things
**Выполнили все задания:** Пиякин Павел, Сисимирова Дарья

**Содержание:**

**5 семестр**
1. Светофор [traffic_light](https://github.com/Deppkepa/Internet_of_Things/tree/main/traffic_light)
2. Детектор источника света [light_source_detector](https://github.com/Deppkepa/Internet_of_Things/tree/main/light_source_detector)
3. [LedPhotoDistributedSerial](https://github.com/Deppkepa/Internet_of_Things/tree/main/LedPhotoDistributedSerial)
4. [MQTT](https://github.com/Deppkepa/Internet_of_Things/tree/main/MQTT)
5. [LedMatrix8x8](https://github.com/Deppkepa/Internet_of_Things/tree/main/LedMatrix8x8)
6. [LedMatrix](https://github.com/Deppkepa/Internet_of_Things/tree/main/LedMatrix)
7. [ESP_Lamp](https://github.com/Deppkepa/Internet_of_Things/tree/main/ESP_Lamp)

**6 семестр**
1. [ButtonBounceProcessing](https://github.com/Deppkepa/Internet_of_Things/tree/main/Bounce_Processing)
2. [I2C_chat](https://github.com/Deppkepa/Internet_of_Things/tree/main/I2C_chat)
3. [H-bridge](https://github.com/Deppkepa/Internet_of_Things/tree/main/H-bridge)
4. [PROJECT](https://github.com/Deppkepa/Internet_of_Things/tree/main/PROJECT)
5. [ButtonMatrix](https://github.com/Deppkepa/Internet_of_Things/tree/main/ButtonMatrix)
6. [SPI](https://github.com/Deppkepa/Internet_of_Things/tree/main/SPI)

**Примечания:**
1. Ссылки на видео реализацию все разные!

## 1. Светофор
**Реализация:**

**Принципиальная схема соединения светофора:**

![картинка 1](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/null%20(1).png)

**Сборка в симуляторе:**

![картинка 2](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/Grand%20Tumelo-Jaban.png)

**Провода:**

* Красный провод - 10 пин
* Зеленый провод - 13 пин
* Желтый провод - 12 пин
* Черный провод - GND

Результат представлен в виде видео по сылке в яндекс облако: https://disk.yandex.ru/d/ukZcg-8z1LOr3A
## 2. Детектор источника света
**Реализация:**

**Принципиальная схема соединения:**
![картинка 4](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/детектор%20источника%20света.png)

**Сборка в симуляторе:**
![картинка 5](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/Tremendous%20Borwo-Duup.png)

**Провода:**

* Красный провод - 5V
* Черный провод - GND
* Синий провод - 12 пин
* Зеленный провод - 13 пин
* Бирюзовый провод - A1
* Фиолетовый провод - A2

**Результат представлен в виде видео по сылке в яндекс облако:** https://disk.yandex.ru/d/dWRPdsrrdzvtHA

## 3. LedPhotoDistributedSeria
**Реализация:**

**Принципиальная схема соединения:**
![картинка 6](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/микро_светодиод_и_резистор.png)

**Сборка в симуляторе:**
![картинка 7](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/микроконтролеры.png)

**Провода:**

* Черный провод - GND
* Красный повод - 5V
* Синий провод - 13Pin
* Желтый провод - A1

**Результат представлен в виде видео по сылке в яндекс облако:**  https://disk.yandex.ru/d/4jmyvvxnl5-yjw

**Инструкция по запуску:**
 1. Скачать репозиторий по удобному способу
 2. Зайти в папку с заданием: [LedPhotoDistributedSerial](https://github.com/Deppkepa/Internet_of_Things/tree/main/LedPhotoDistributedSerial)
 3. Выбрать какая ардуинка будет отвечать за светодиод и какая за фоторезистор
 4. Запустить прошивку для светодиода из папки `blink`
 5. Запустить прошивку для фоторезистора из папки `photoval`
 6. Открыть файл `main.py из папки `micro_avto` и поменять в соотвествии с вашими портами на ардуинках (в файле указаны порты для оп windows)
 7. Запустить `main.py`
 8. Готово

## 4. MQTT
**Реализация:**

**Принципиальная схема соединения:**
![картинка 8](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/MQTT(схема%20ручками).png)

**Сборка в симуляторе:**

Собрать отдельно платы для фоторезистора и для светодиода. Эти схемы можно посмотреть выше. Обязательно на разных платах и подключаются к разным пк!

**Результат представлен в виде видео по сылке в яндекс облако:**  https://disk.yandex.ru/d/Iv0D8uaaHF6O3w

**Инструкция по запуску:**
 1. Скачать репозиторий по удобному способу
 2. Зайти в папку с заданием: [MQTT](https://github.com/Deppkepa/Internet_of_Things/tree/main/MQTT)
 3. Выбрать какая плата будет отвечать за светодиод и какая за фоторезистор. Далее выбрать пк, которые будут отвечать за светодиод и фоторезистор.
 4. Прошить плату фоторезистора (`Photoval.ino`), а затем запустить код `publisher.py`. Эти файлы отвечают за фоторезистор. (не забыть поменять "COM" в `publisher.py`)
 6. Прошить плату светодиода (`Led.ino`), а затем запустить код `sub.py`. Эти файлы отвечают за светодиод. (не забыть поменять "COM" в `sub.py`)
 7. Подождать пока найдётся `pub_id`
 8. Выбрать топик (`instant`, `averge`, `min_max`)

## 5. LedMatrix 8x8
**Реализация:**

**Принципиальная схема соединения:**

![картинка 9](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/led%20matrix-2.png)

**Сборка в симуляторе:**

Нет возможности представить.

**Результат представлен в виде видео по сылке в яндекс облако:**  https://disk.yandex.ru/d/lqftMznwoQMlIQ

## 6. LedMatrix
**Реализация:**

**Принципиальная схема соединения:**

![картинка 10](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/led-matrix.png)
+ сборку светодиода можно посмотреть выше

**Сборка в симуляторе:**
Нет возможности представить.

**Результат представлен в виде видео по сылке в яндекс облако:**  https://disk.yandex.ru/d/Azr1dP0dscmzMQ

## 7. ESP_Lamp
**Реализация:**

**Принципиальная схема соединения:**
Вам понадобится только плата esp8266 и компьютер с программой

**Результат представлен в виде видео по сылке в яндекс облако:**  https://disk.yandex.ru/d/4ilGFM3DnPwFMA

# 6 семестр

## 1. ButtonBounceProcessing
**Примечания:**

- Это задание делалось индивидуально каждым участником репозитория. Поэтому, чтобы не создавать отдельный репозиторий для соавтора, было принято решение создать две папки с вариантами решения обоих участников.
- Схема и сборка использовались обоими участниками

**Реализация:**

**Принципиальная схема соединения:**

![картинка 11](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/Button%20(ручками).jpg)


**Сборка в симуляторе:**

Для тестирования кода на дребезг использовался сайт wokwi и сборка от туда.

![картинка 12](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/Button.png)

**Результат представлен в виде видео по сылке в яндекс облако:**  

- Даша: https://disk.yandex.ru/d/6R_b9pG8yUK1cw
- Паша: https://disk.yandex.ru/i/b0HSoYalCHxpFA

## 2. I2C_chat
**Реализация:**
**Описание протокола обмена для подключения устройств по I2C**

Данный протокол предназначен для обмена данными между мастером (который может выступать микроконтроллер) и ведомыми устройствами (например, датчиками или исполнительными модулями) по интерфейсу I2C. Описание предназначено для разработчиков сторонних устройств, желающих интегрироваться в нашу сеть.

**Аппаратные требования**

- Ваша плата/устройство должно поддерживать I2C (режим slave).

**Адресация устройств**

- Каждый slave-узел имеет уникальный адрес на шине I2C. Из-за чего адрес нового slave устройства задаётся в файле `master.ino` в структурах `tab_name`,  `tab_messager`. На картинке представлен кусочек кода куда надо вставить адрес устройства и в каком формате.
- Адресс slave устройств должен быть обязательно уникальным.
  
![картинка 13](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/Пример%20кода%20I2C.png)

**Формат сообщений**

Обмен состоит из пакетов — буфер небольшой, примерно 32 байта.

**Формат запроса**

Из любого slave устройства который инициализирован в табличке в мастере. Пишем другому slave устройству. Формат обращения в slave устройствах. <Имя кому отправить сообщение>@ <сообщение>.Тут обязательно должен присутвовать разделитель. Чтобы ответить slave устройству на сообщение отправляется сообщение формата. <Сообщение>.

Например: 

file: `slave.ino`

Пишет в серийную консоль: `Dasha@ Hey bro how do you do?` (длина сообщения 29)

file: `slave_dasha.ino`

Появляется надпись в серийной консоли: `От Pasha: Hey bro how do you do?`
В ответ слейву отправляем: `Hello` (длина сообщения 5)

file: `slave.ino`

Появляется надпись в серийной консоли: `От Dasha: Hello` 


**Важно!** мастер от пользователя никакие сообщения не принимает.

**Принципиальная схема соединения:**

![картинка 14](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/микроконтролеры.jpg)

**Сборка в симуляторе:**

![картинка 15](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/microcontrollers.png)

**Результат представлен в виде видео по сылке в яндекс облако:** https://disk.yandex.ru/d/lrH28QFnNIBVCA 


## 3. H-bridge
**Реализация:**

**Сборка в симуляторе:**

Для тестирования проводились на tinkercad.

![картинка 16](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/H-bridge.png)
Провода:
* Черные провода - GND
* Красные провода - +
* Фиолетовый провод - Enable 1 & 2
* Голубые провода - Input
* Зеленные провода - Output

**Результат представлен в виде симуляции на сайте tinkercad:**  

https://www.tinkercad.com/things/2MESM0L3w6Q-h-bridge?sharecode=elsh0bsA0cope7HGBIOnmNCZTBlehkitVAhbjqIdsJ0

## 4. PROJECT
**Описание:**

![картинка 19](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/PROJECT1.png)
![картинка 20](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/PROJECT2.png)

Станция, показывающая данные о погоде в Иркутске.
Состоит из TFT дисплея 1.8'' ST7735S, wemos D1 mini, корпуса и шнура питания.
![картинка 21](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/PROJECT_scheme2.jpg)

В проекте присутствует 7 модулей:PROJECT.ino, Config.h, Display.h, Server.h, WeatherAPI.h, WeatherIcons.h, WIFI.h
![картинка 22](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/PROJECT_scheme1.png)

Wemos d1 mini и TFT 1.8'' ST7735S сообщаются по SPI
![картинка 22](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/PROJECT_scheme3.jpg)

**Use-case:**

1.  Питание подключено к устройству.
2.  Выведется надпись Starting...
3.  При первичном запуске поднимется точка ESP_WiFi (об это сообщится на экране), к которой пользователь должен подключится, перейти по ip адресу на экране и ввести данные своей wifi сети и город, погоду которого нужно транслировать; При повторном запуске (данные wifi и города пользователя есть в памяти на устройстве) атоматически произойдёт подключение к сети.
4.  3 попытки подключения, в случае неудачи возвращается на шаг 3.
5.  Попытка получить данные о погоде с помощью API OpenWeatherMap, при неудаче надпись на экране API Error и повторная попытка.
6.  3 Api Error, надпись "Слишком много Api Error, поднимаю точку доступа" и вернётся на шаг 3.
7.  Отображение данных о погоде на экране устройства. Обновляются раз в 10 минут.
![картинка 23](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/PROJECT_scheme4.jpg)

**API:**

Структура запроса:
![Картинка 24](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/PROJECT_scheme5.png)

Структура JSON ответа:

```                          
{
   "coord": {
      "lon": 7.367,
      "lat": 45.133
   },
   "weather": [
      {
         "id": 501,
         "main": "Rain",
         "description": "moderate rain",
         "icon": "10d"
      }
   ],
   "base": "stations",
   "main": {
      "temp": 284.2,
      "feels_like": 282.93,
      "temp_min": 283.06,
      "temp_max": 286.82,
      "pressure": 1021,
      "humidity": 60,
      "sea_level": 1021,
      "grnd_level": 910
   },
   "visibility": 10000,
   "wind": {
      "speed": 4.09,
      "deg": 121,
      "gust": 3.47
   },
   "rain": {
      "1h": 2.73
   },
   "clouds": {
      "all": 83
   },
   "dt": 1726660758,
   "sys": {
      "type": 1,
      "id": 6736,
      "country": "IT",
      "sunrise": 1726636384,
      "sunset": 1726680975
   },
   "timezone": 7200,
   "id": 3165523,
   "name": "Province of Turin",
   "cod": 200
}                    
```                        

## 5. ButtonMatrix
**Реализация:**

**Сборка в симуляторе:**

Для тестирования проводились на tinkercad.

![картинка 17](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/button-matrix.png)


**Результат представлен в виде симуляции на сайте tinkercad:**  

https://www.tinkercad.com/things/2gjYw5cMepE-buttonmatrix

## 6. SPI
**Реализация:**

**Сборка:**

![картинка 18](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/spi1.png)


**Результат представлен в виде демонстраии по ссылке:**  
https://disk.yandex.ru/i/-hYSn4lXj67lSg









