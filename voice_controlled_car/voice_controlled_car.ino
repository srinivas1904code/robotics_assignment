#include<SoftwareSerial.h>
SoftwareSerial bluetooth(3,4); //(RX,TX)  to uno i.e., 3 acts as reciever for arduino
char bt;
String data,temp;
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
  // if(bluetooth.available()){
  //   bt = bluetooth.read();
  //   Serial.println("the character from bluetooth is:"+String(bt));
  // } 
while(bluetooth.available()){
    bt = bluetooth.read();
    temp+=bt;
    delay(10);//this delay deals with latency issues
  } 
  if(temp.length()>0){
    data = temp;
    Serial.println("the string is:"+String(data));
  }
  if(data == "forward"){
   forward();
   delay(2);
 }
 else if(data == "left"){
   left();
   delay(2);
 }
 else if(data == "right"){
   right();
   delay(2);
 }
 else if(data == "backward"){
   backward();
  delay(2);   
 }
 else if(data == "stop"){
 stop(2);
 }
temp = "";
}