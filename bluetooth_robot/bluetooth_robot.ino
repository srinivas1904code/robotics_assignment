#include<SoftwareSerial.h>
SoftwareSerial bluetooth(4,3); //(RX,TX) rx to uno 
char bt='0';
void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("pair with bluetooth");
}
void stop(int n){
for(int i=0;i<n;i++){  
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  delay(1);
}  
}
void left(){
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
}
void right(){
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);  
}
void forward(){
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);  
}
void backward(){
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(bluetooth.available()){
    bt = bluetooth.read();
    Serial.println("the character from bluetooth is:"+String(bt));
  } 
  if(bt == '8'){
   forward();
   delay(2);
 }
 else if(bt == '4'){
   left();
   delay(2);
 }
 else if(bt == '6'){
   right();
   delay(2);
 }
 else if(bt == '2'){
   backward();
  delay(2);   
 }
 else if(bt == '0'){
 stop(2);
 }
}
