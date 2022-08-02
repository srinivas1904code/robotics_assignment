int lefts,rights;
void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
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
  lefts = analogRead(A0);
  rights = analogRead(A2);
  Serial.println("values of left and right sensor:  "+String(lefts)+"   "+String(rights));
  delay(10);
  if(rights>500 && lefts>180){ //object is detected by both the sensors
  stop(2); 
  forward();
  delay(40); //i.e., it should follow straight
  }
  if(rights<500 && lefts<180){ //no obstacle is detected so robot should stop
    stop(3);
  }
  if(rights>500 && lefts<180){ //obstacle is detected in right side so turn right
      stop(2);
      right();
      delay(40);
  }
if(rights<500 && lefts>180){ //obstacle is detected in left side 
  stop(2);
  left(); //so turn left
  delay(40);
}
  
}
