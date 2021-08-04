#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>

Adafruit_BME280 bme; // I2C

float h, t, p, pmm;
char temperatureString[6];
char humidityString[6];
char pressureString[7];
char pressuremmString[7];

int BME_mtbs = 1000; // как часто забирать сообщения
long BME_lasttime;

void startBME() {
    Serial.println(F("BME280 test"));
    Wire.begin(D6, D5);
    Wire.setClock(100000);
    if (!bme.begin(0x76)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    else
    {
        Serial.println("BME280 sensor is finded!");
    }
    
}

void getWeather() {
    h = bme.readHumidity();
    t = bme.readTemperature() - 2;
    p = bme.readPressure()/100.0F;
    pmm = p * 0.75;
    dtostrf(t, 5, 1, temperatureString);
    dtostrf(h, 5, 1, humidityString);
    dtostrf(p, 6, 1, pressureString);
    dtostrf(pmm, 6, 1, pressuremmString);
}