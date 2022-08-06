void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
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

void loop(){
 int d0 = digitalRead(4);
 int d1 = digitalRead(5);
 int d2 = digitalRead(6);
 int d3 = digitalRead(7);
 int num = d3*8+d2*4+d1*2+d0;
 if(num == 2){
   stop(2);
   forward();
   delay(20);
 }
 else if(num == 4){
   stop(2);
   left();
   delay(20);
 }
 else if(num == 6){
   stop(2);
   right();
   delay(20);
 }
 else if(num == 8){
   stop(2);
   backward();
  delay(20);   
 }
 else if(num == 5){
 stop(2);
 }
}
