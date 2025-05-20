#ifndef CONFIG_H
#define CONFIG_H

// TFT pins
#define TFT_CS     D8
#define TFT_RST    D4
#define TFT_DC     D3

// Wi-Fi AP settings
const String ssidAP = "ESP_WiFi";
const String passwordAP = "12345678";

// Wi-Fi Client settings
const char* ssidCLI = "";
const char* passwordCLI = "";

// Weather API settings
const String API_KEY = "24ee95b2cd78b919fa583c775cb4142d";
const String CITY = "Irkutsk";
const String WEATHER_URL = "http://api.openweathermap.org/data/2.5/weather?q=" + CITY + "&appid=" + API_KEY + "&units=metric"+"&lang=en";

// Intervals
const unsigned long WEATHER_UPDATE_INTERVAL = 10000;//600000; // 10 минут
const unsigned long WIFI_CHECK_INTERVAL = 10000; // 10 секунд

// Wi-Fi status
bool AP_UP = false;
bool wifi_connected = false;
bool cant_connect_wifi = false;

String ip_="";



#endif