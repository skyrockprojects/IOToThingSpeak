//define for sensor
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN            2         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT11     // DHT 11 
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

//customize esp8266 lib
#include "ESP8266.h"
const char *SSID     = "SkyrockProjects2";
const char *PASSWORD = "rememberable";

SoftwareSerial mySerial(10, 11); //SoftwareSerial pins for MEGA/Uno. For other boards see: https://www.arduino.cc/en/Reference/SoftwareSerial

ESP8266 wifi(mySerial); 

float temp;
float humi;

void setup(void)
{
  //Start Serial Monitor at any BaudRate
  Serial.begin(57600);
  Serial.println("Begin");
  //sensor init
  dht.begin();
  Serial.println("Sensor init");
  sensor_t sensor;

  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  delayMS = sensor.min_delay / 1000;
  //check wifi status
  if (!wifi.init(SSID, PASSWORD))
  {
    Serial.println("Wifi Init failed. Check configuration.");
    while (true) ; // loop eternally
  }
}


void loop(void)
{   

    // Delay between measurements.
   delay(delayMS);
   sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    temp = event.temperature;
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    humi = event.relative_humidity;
    Serial.println("%");
  } 
    
    //Serial.println(temp);
    //Serial.println(humi);
    
    char result_a[5] = "";
    char result_b[5] = "";
    Serial.println("Sending Request");
    //send request httpGet(char* temp) -- temp will be sensor variable    
    wifi.httpGet(dtostrf(temp, 3, 2, result_a));// you can add second parameter into function

    delay(10000);
}








