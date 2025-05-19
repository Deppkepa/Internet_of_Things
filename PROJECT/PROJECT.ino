#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>


#define TFT_CS     D8  
#define TFT_RST    D4  
#define TFT_DC     D3  


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);        // Поворот экрана (1 = 90 градусов, может быть 0, 2, 3)
  
  // Очистка экрана
  tft.fillScreen(ST77XX_BLACK);
  
  // Установка цвета текста и размера
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  
  // Вывод текста
  tft.setCursor(0, 0); // Установка курсора в верхний левый угол
  tft.println("Hello, Wemos!");
}

void loop() {
  
}
