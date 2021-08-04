#include <ESP8266FtpServer.h>             // Библиотека для работы с SPIFFS по FTP
#include <TelegramBot/TelegramBot.h>
#include <WebServer/WebServer.h>
#include <BME280/BME280.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
extern bool debug;


FtpServer ftpSrv;                         // Создаём объект для работы с FTP

extern const char* ssid ;            // Указываем имя WiFi-сети, к которой будет подключаться ESP8266 для доступа в Интернет
extern const char* password;        // Указываем пароль для подключения к WiFi-сети


void start_system() {
  Serial.begin(9600);
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready OTA");
  startWebServer();
  SPIFFS.begin();                         // Инициализируем работу с файловой системой
  startBot();
  ftpSrv.begin("login","password");       // Инициализируем FTP-сервер (на 21-й порт)
  startBME();
}


void setup() {
  start_system();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED){
    ArduinoOTA.handle();
    handleClient();
    ftpSrv.handleFTP();                     // Отслеживаем обращения по FTP 
    if (!debug)
    {
      checkMessages();
    }
  }else{
    start_system();
  }
}
