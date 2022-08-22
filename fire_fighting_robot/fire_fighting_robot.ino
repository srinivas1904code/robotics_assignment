int rig,lef,mid;
void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT); 
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
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
void stopFire(){
  int val = analogRead(A1);
  digitalWrite(9,HIGH);
  while(val>700){
    val = analogRead(A1);
    delay(800);        
    forward();
    delay(200);
    stop(2);
}
  digitalWrite(9,LOW);
}
void loop(){
// right sensor A0,middle sensor - A1, left sensor-A2
rig = analogRead(A0);
mid = analogRead(A1);
lef = analogRead(A2);

Serial.println("right: "+String(rig)+"  middle: "+String(mid)+"left: "+String(lef));

if((lef < 200)&&(rig < 200)&&(mid<200)){
 stop(3);
 digitalWrite(9,LOW);
 delay(2);
}
else
{
  if((lef> mid)&&(lef>rig)){
    left();
    delay(100);
    stop(100);
}
else if((rig > mid)&&(rig > lef)){
  right();
  delay(100);
  stop(100);
}
else if((mid > lef)&&(mid > rig)&&(mid<700)){
  forward();
  delay(100);
  stop(100);
}
else if((mid > lef)&&(mid > rig)&&(mid > 700)){
  stop(1);
  stopFire();
}
}
}
