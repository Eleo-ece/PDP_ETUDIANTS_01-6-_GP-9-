#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Define the pins that we will use
#define SENSOR 33
#define LED 26

#define DHTPIN 33 // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
// #define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE DHT11 // DHT 22 (AM2302)
// #define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

#define Conversion 1000000 // Conversion de ms à secondes
#define TIME_TO_SLEEP 5    // Temps de veille de l'ESP32 (en secondes)

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup()
{
  Serial.begin(9600);
  // Initialise l'appareil
  dht.begin();

  pinMode(LED, OUTPUT);

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  // Afficher une température avec un peu de formatage
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
  {
    Serial.println(F("Error reading temperature!"));
  }
  else
  {
    Serial.print(F("\n\nTemperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  // Afficher l'humidité relative avec un peu de formatage
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    Serial.println(F("Error reading humidity!"));
  }
  else
  {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * Conversion);
  Serial.println("Mise en veille de l'ESP32 toutes les " + String(TIME_TO_SLEEP) + " secondes");

  Serial.println("Mise en veille");
  delay(1000);

  Serial.flush();
  esp_deep_sleep_start();
  Serial.println("Ce message ne sera jamais affiché");
}

void loop()
{
}