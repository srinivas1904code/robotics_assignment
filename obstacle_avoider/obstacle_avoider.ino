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
  delay(50);
  if(rights>500 && lefts>180){ //object is detected by both the sensors
    stop(100);
    backward();
    delay(450);
    left();
    delay(1200);// steep left turn(turn greater than 60degrees)
  }
  if(rights<500 && lefts<180){ //no obstacle is detected so robot should propogate forward
    forward();
    delay(400);
  }
  if(rights>500 && lefts<180){ //obstacle is detected in right side so turn left
      stop(100);
      backward();
      delay(350);
      left();
      delay(500);
  }
if(rights<500 && lefts>180){ //obstacle is detected in left side 
  stop(100);
  backward();
  delay(350);
  right(); //so turn right
  delay(500);
}
  
}
