#ifndef CONSTANTS
#define CONSTANTS
//  File Name : LibConstants.hpp    Purpose : Global Constants for Lib Utils
namespace SSIDConsts
{
    char* ssid = "";            // Указываем имя WiFi-сети, к которой будет подключаться ESP8266 для доступа в Интернет
    char* password = "";        // Указываем пароль для подключения к WiFi-сети
}

namespace TelegramConsts
{
    char* token = "";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
}

namespace MySSIDConsts
{
    char* mySsid = "SmartHome";
}
#endif