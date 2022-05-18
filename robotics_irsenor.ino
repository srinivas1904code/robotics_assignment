void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT); // positive terminal to 11 and negative to pin 10
  pinMode(11,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorvalue = analogRead(A0);
  if(sensorvalue>500){
   digitalWrite(10,HIGH);
   digitalWrite(11,LOW); //rotates in clockwise direction if sensor detects object
  }
  else{
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);//rotates in anticlockwise if the object is not detected
  }
 
}
