#include "DHT.h"

#define DHTp 2  // pin no 2 for exchange of data
#define DHTt DHT11 //model of sensor
DHT dht(DHTp,DHTt);

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  dht.begin();
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true); // reads temperature in fahrenheit
if(isnan(h) || isnan(t)|| isnan(f)){
  Serial.println("Failed to read from DHT sensor!");
  return;
}
float hif = dht.computeHeatIndex(f,h);
float hic = dht.computeHeatIndex(t,h,false);
Serial.print(F("Humidity: "));
Serial.println(h);
if(h>63){   // at present condition the moisture is around 57 hence we set the thresold to 63
digitalWrite(13,HIGH); // on board led glows when the moisture level go above 63
delay(4000);
}
else{
digitalWrite(13,LOW);  // on board led does not glows when the moisture level goes below 63
}
}
