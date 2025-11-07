//////DHT Sensor initialization
#include "DHT.h"
#define DHTPIN 7 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//////

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(13, OUTPUT);
  
}

void loop() {
  digitalWrite(13,HIGH); //we use port 13 a voltage source
 // publish a message roughly every 1 second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();

    String msg = Sensor2();

    Serial.println(msg);
  }

}
String Sensor1(){
/////MQ5 Gas sensor

  String sensor1 = "\"GAS\":" + String(analogRead(A0)) + ",";

  return sensor1.c_str();

}

String Sensor2(){
/////DHT21 humidity & temperature sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //simple approximation of dew point (dp) is calculated next
  //below 0 degrees C, this approximates the frost point
  //https://www.thunderscientific.com/wp-content/uploads/2022/12/TSC-3900-DPAnalysis-Rev-E.pdf
  float dp = t - (100 - h)/5; 

  //Set both values to zero if the sensor is faulty
  if (isnan(h) || isnan(t)) {
    h = 0; t = 0;
  }

  //Output contains both humidity and temperature values in JSON-compatible format
  String sensor2 = "{\"H\":" + String(h) + "," + "\"T\":" + String(t) + "," + "\"DP\":" + String(dp) + "}";

  return sensor2.c_str();

}