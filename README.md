# Internet_of_Things
**Выполнили все задания:** Пиякин Павел, Сисимирова Дарья

**Содержание:**

1. Светофор [traffic_light](https://github.com/Deppkepa/Internet_of_Things/tree/main/traffic_light)
2. Детектор источника света [light_source_detector](https://github.com/Deppkepa/Internet_of_Things/tree/main/light_source_detector)
3. [LedPhotoDistributedSerial](https://github.com/Deppkepa/Internet_of_Things/tree/main/LedPhotoDistributedSerial)

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
![картинка 6]()

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
