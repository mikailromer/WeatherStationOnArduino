#include <Wire.h>
#include <DS3231.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN 8     
#define DHTTYPE    DHT11     

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
uint8_t counter=0;
float temperature,humidity;

DS3231 clock;
RTCDateTime date;
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
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

 //LCD displayer 16x2 initialization

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("T: ");
  lcd.print(date.hour);
  lcd.print(":");
  lcd.print(date.minute);
  lcd.print(":");
  lcd.print(date.second);
  lcd.setCursor(0,1);
  lcd.print(date.hour);
 

}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  temperature=event.temperature;
  Serial.print(temperature);
  Serial.print(",");
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  humidity=event.relative_humidity;
  Serial.println(humidity);
  // Time reading
  date = clock.getDateTime();

  //LCD displayer time typing
  //Time is actualized once per second
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.print(date.hour);
  lcd.print(":");
  lcd.print(date.minute);
  lcd.print(":");
  lcd.print(date.second);
  
  if(counter==0)
  {
    //LCD displayer temperature and relative humidity typing
    //Temperature and humidity are actualized once per 10 seconds
    lcd.setCursor(0,1);
    if (!(isnan(event.temperature)) && !(isnan(event.temperature))) {
      lcd.print("T:");
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
    //After each 10 seconds LCD screen is cleaned.
    counter=0;
    lcd.clear();
  }
}
