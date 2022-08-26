int rig,mid,lef;
void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
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

void leftTurn(){
  int m_tem = 1;
  while(m_tem!=0){
    left();
    delay(50);
    stop(100);
    m_tem = digitalRead(3);
    int r_tem = digitalRead(4);
    if(r_tem == 0){
      m_tem = 0;
    }
  }
}

void rightTurn(){
  int l_tem = 1;
  while(l_tem!=0){
    right();
    delay(50);
    stop(100);
    l_tem = digitalRead(2);
    int m_tem= digitalRead(3);
    if(m_tem == 0){
      l_tem=0;
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  // 0 is the output when the black line is detected, where as 1 is the output when white surfce is detected  
 lef = digitalRead(2);
 rig = digitalRead(4);
 mid = digitalRead(3);
 if((lef == 0)&&(mid == 0)&&(rig == 1)){
   leftTurn();  // because the left T-segment is identified
 }
  if((lef == 0)&&(mid == 1)&&(rig == 0)){
   leftTurn();  // because the vertical T-segment is identified
 }
   if((lef == 0)&&(mid == 1)&&(rig == 1)){
   leftTurn();  // because the left turn is identified
 }
  if((lef == 1)&&(mid == 0)&&(rig == 0)){
   forward();  // because the right-T is identified
   delay(80);
   stop(50);
 }
 if((lef ==1)&&(mid==0)&&(rig ==1)){
  forward();
  delay(100);
  stop(70);
 }
  if((lef == 1)&&(mid == 1)&&(rig == 0)){
   forward();
   delay(100);
   stop(70);
   rightTurn();  // because the right turn is identified
 }
   if((lef == 1)&&(mid == 1)&&(rig == 1)){
   forward();
   delay(150);
   stop(70);// dead end is identified or robot move out of path- turn back if dead end
   int l_temp = digitalRead(2);
   int m_temp = digitalRead(3);
   int r_temp = digitalRead(4);
   if((lef == 1)&&(mid == 1)&&(rig == 1)){
     leftTurn(); 
   }
   }
   if((lef == 0)&&(mid == 0)&&(rig == 0)){
   forward();
   delay(150);
   stop(70);// 4-way intersection or maze end area identified
   int l_temp = digitalRead(2);
   int m_temp = digitalRead(3);
   int r_temp = digitalRead(4);
   if((lef == 0)&&(mid == 0)&&(rig == 0)){
    exit(0); 
   }
   else{
     leftTurn();
   }
   }   
}
