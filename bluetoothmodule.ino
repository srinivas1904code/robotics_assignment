#include<SoftwareSerial.h>
SoftwareSerial bluetooth(12,7); //(RX,TX) rx to uno 
char bt='0';
void setup() {
  // put your setup code here, to run once:
  bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("pair with bluetooth");
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(bluetooth.available()){
    bt = bluetooth.read();
    Serial.println("the character from bluetooth is:"+String(bt));
  }  
  switch(bt){
    case 'C':
        digitalWrite(13,HIGH);
        break;
    case 'D':
        digitalWrite(13,LOW);
        break;
  }
  }
