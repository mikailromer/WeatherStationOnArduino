#include <Wire.h>
#include <DS3231.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>
#include <stdio.h>

#define DHTPIN 8     
#define DHTTYPE    DHT11     // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
uint8_t counter=0;
float temperature,humidity;

DS3231 clock;
RTCDateTime dt;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


void setup() {
  Serial.begin(9600);
 
  // Initialization of DS3231 RTC
  //Serial.println("Initialize DS3231");;
  clock.begin();
 
  // Set date and actual hour
  clock.setDateTime(__DATE__, __TIME__);

  //Settings for DHT11 Temperature & Humidity Sensor
  // Initialize device.
  dht.begin();
  //Serial.println(F("DHT11 Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  /*
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  */
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  /*
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  */
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

 //LCD displayer 16x2 initialization

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("T: ");
  lcd.print(dt.hour);
  lcd.print(":");
  lcd.print(dt.minute);
  lcd.print(":");
  lcd.print(dt.second);
  lcd.setCursor(0,1);
  lcd.print(dt.hour);
 

}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    //Serial.println(F("Error reading temperature!"));
  }
  else {
  //  Serial.print(F("Temperature: "));
    //Serial.print(event.temperature);
    temperature=event.temperature;
    Serial.print(temperature);
    Serial.print(",");
   // Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
   // Serial.println(F("Error reading humidity!"));
  }
  else {
   // Serial.print(F("Humidity: "));
    humidity=event.relative_humidity;
    Serial.println(humidity);
    //Serial.println(F("%"));
  }
  

  
  // Time reading
  dt = clock.getDateTime();
  /*
  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  */
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.print(dt.hour);
  lcd.print(":");
  lcd.print(dt.minute);
  lcd.print(":");
  lcd.print(dt.second);
  
  if(counter==0)
  {
    lcd.setCursor(0,1);
    if (!(isnan(event.temperature)) && !(isnan(event.temperature))) {
      char temp_string[4], hum_string[4];
      lcd.print("T:");
      //Serial.println(temperature);
      lcd.print(temperature);
      lcd.print("C");
      lcd.print(" H:");
      lcd.print(int(humidity));
      lcd.print("%");
    }
  }
  
  counter=counter+1;
  if(counter==10)
  {
    counter=0;
    lcd.clear();
  }
 
  
 
  //delay(1000);

}
