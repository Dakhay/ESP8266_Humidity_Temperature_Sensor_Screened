#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include <GyverOLED.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);
GyverOLED<SSH1106_128x64> oled;

void printUI()
{
  oled.home();

  oled.setCursorXY(10, 8);
  oled.setScale(1);
  oled.print("Temp : ");

  oled.setScale(1);
  oled.setCursorXY(10, 40);
  oled.print("Humi : ");
 
  oled.update();
}

void setup()
{
  Serial.begin(9600);
  dht.begin();

  delay(1000);

  oled.init();
  oled.clear();
  oled.update();
  printUI();
  oled.setScale(2);
}

void loop()
{
  sensors_event_t event;

  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
  {
    Serial.println("Erreur de lecture de la temperature !");
  }
  else
  {
    Serial.print("Temperature: ");
    Serial.print(event.temperature, 2);
    Serial.println(" C");
    oled.setScale(2);
    oled.setCursorXY(50, 8);
    oled.print(event.temperature, 1);
    oled.setScale(1); 
    oled.setCursorXY(102, 5);
    oled.print("o");
    oled.setScale(2); 
    oled.setCursorXY(110,8);
    oled.print("C");
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    Serial.println("Erreur de lecture de l'humidite !");
  }
  else
  {
    Serial.print("Humidite: ");
    Serial.print(event.relative_humidity, 2);
    Serial.println(" %");
    oled.setScale(2);
    oled.setCursorXY(50, 40);
    oled.print(event.relative_humidity, 1);
    oled.setScale(2);
    oled.setCursorXY(110, 40);
    oled.print("%");
  }
  oled.update();
  delay(1000);
}
