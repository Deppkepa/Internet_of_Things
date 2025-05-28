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

**Алгоритм работы:**

1.  Питание подключено к устройству.
2.  Выведется надпись Starting...
3.  При первичном запуске поднимется точка ESP_WiFi (об это сообщится на экране), к которой пользователь должен подключится, перейти по ip адресу на экране и ввести данные своей wifi сети и город, погоду которого нужно транслировать; При повторном запуске (данные wifi и города пользователя есть в памяти на устройстве) атоматически произойдёт подключение к сети.
4.  3 попытки подключения, в случае неудачи возвращается на шаг 3.
5.  Попытка получить данные о погоде с помощью API OpenWeatherMap, при неудаче надпись на экране API Error и повторная попытка.
6.  3 Api Error, надпись "Слишком много Api Error, поднимаю точку доступа" и вернётся на шаг 3.
7.  Отображение данных о погоде на экране устройства. Обновляются раз в 10 минут.
![картинка 23](https://github.com/Deppkepa/Internet_of_Things/blob/main/images/PROJECT_scheme4.jpg)

**Use-case:**

1. Пользователь включает питание устройства
2. Следует инструкции на экране и подключается к сети Esp_wifi
3. Вводит на сайте данные wifi сети и города
4. Смотрит погоду раз в 10 минут

1. Пользователь включает питание устройства
2. Устройство подсоединяется к запомненной сети wifi и получает данные о погоде запомненного города
3. Пользователь смотрит погоду раз в 10 минут


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
                  
**Демонстрация:**

https://disk.yandex.ru/i/_CqILB1kn1J4YA
